#ifndef SERIALWRAPPER_H
#define SERIALWRAPPER_H

#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include <Stream.h>

#define SERIAL_CANVAS_WIDTH 320
#define SERIAL_CANVAS_HEIGHT 80
#define SERIAL_BUFFER_HEIGHT 720

constexpr int interleaveFrames = 20;

GFXcanvas1 _serialCanvas(SERIAL_CANVAS_WIDTH, SERIAL_CANVAS_HEIGHT);
GFXcanvas1 _serialBufferCanvas(SERIAL_CANVAS_WIDTH, SERIAL_BUFFER_HEIGHT);
GFXcanvas1 _serialLastCanvas(SERIAL_CANVAS_WIDTH, SERIAL_CANVAS_HEIGHT);
GFXcanvas1 _serialErasePixels(SERIAL_CANVAS_WIDTH, SERIAL_CANVAS_HEIGHT);
GFXcanvas1 _serialAddPixels(SERIAL_CANVAS_WIDTH, SERIAL_CANVAS_HEIGHT);
GFXcanvas1 _interleaveCanvas(SERIAL_CANVAS_WIDTH, SERIAL_CANVAS_HEIGHT / interleaveFrames);

enum RenderState {
  STATE_INIT,
  STATE_INTERLEAVE,
  STATE_FINAL,
  STATE_IDLE
};

// SerialInterceptor class definition
class SerialInterceptor : public Stream {
public:
  SerialInterceptor(USBCDC &serial, Adafruit_HX8357 &tft)
    : _serial(serial), _tft(tft), _cursorX(0), _cursorY(0), _injectedText(""),
      bufferSize((_serialCanvas.width() + 7) / 8 * _serialCanvas.height()), tweenFrames(2),
      currentOffset(0), state(STATE_IDLE), currentRegion(0), regionHeight(SERIAL_CANVAS_HEIGHT / interleaveFrames) {
  }

  void begin(unsigned long baud) {
    _serial.begin(baud);
  }

  void draw() {
    if (millis() - displayTimer > 240 / interleaveFrames) {
      switch (state) {
        case STATE_INIT:
          currentRegion = 0;
          generateCanvasUpdates(_serialLastCanvas.getBuffer(), _serialCanvas.getBuffer(), _serialErasePixels.getBuffer(), _serialAddPixels.getBuffer(), bufferSize);
          state = STATE_INTERLEAVE;

        case STATE_INTERLEAVE:
          updateSubregion();
          currentRegion++;
          if(currentRegion < interleaveFrames){
            break;
          }
          state = STATE_FINAL;
        case STATE_FINAL:
          state = STATE_IDLE;
          updateCanvas();
        case STATE_IDLE:
          break;
      }
    }
  }

  void updateSubregion() {
    int interleaveYOffset = currentRegion * _interleaveCanvas.height();
    int blitYPosition = 480 - _serialCanvas.height() + interleaveYOffset;

    _interleaveCanvas.fillScreen(0);
    _interleaveCanvas.drawBitmap(0, 0 - interleaveYOffset, _serialAddPixels.getBuffer(),
                                  _serialCanvas.width(), _serialCanvas.height(), HX8357_WHITE);

    _tft.drawBitmap(0, blitYPosition, _interleaveCanvas.getBuffer(),
                    _serialCanvas.width(), _interleaveCanvas.height(), HX8357_WHITE);

    _interleaveCanvas.fillScreen(0);
    _interleaveCanvas.drawBitmap(0, 0 - interleaveYOffset, _serialErasePixels.getBuffer(),
                                  _serialCanvas.width(), _serialCanvas.height(), HX8357_WHITE);

    _tft.drawBitmap(0, blitYPosition, _interleaveCanvas.getBuffer(),
                    _serialCanvas.width(), _interleaveCanvas.height(), HX8357_BLACK);
  }

  void generateCanvasUpdates(uint8_t *canvas1, uint8_t *canvas2, uint8_t *canvas3, uint8_t *canvas4, int buffSize) {
    for (int i = 0; i < buffSize; ++i) {
      // Generate Canvas 3: Pixels unique to Canvas 1 (to erase)
      canvas3[i] = canvas1[i] & ~canvas2[i];

      // Generate Canvas 4: Pixels unique to Canvas 2 (to add)
      canvas4[i] = canvas2[i] & ~canvas1[i];

      canvas1[i] = canvas2[i];
    }
  }

  // Call this method to "inject" text into the Serial input chain.
  void inject(const String &text) {
    _injectedText += text;
  }

  // Write function for output: duplicate to Serial and TFT.
  size_t write(uint8_t data) override {
    // Forward the data to the original Serial
    _serial.write(data);



    return 1;  // Always return 1 for a successful write
  }

  template<typename T>
  size_t print(T const &value) {
    displayTimer = millis();
    state = STATE_INIT;

    // Forward to the underlying Serial
    size_t resultSerial = _serial.print(value);

    // Print the entire string onto the canvas
    size_t resultCanvas = _serialBufferCanvas.print(value);
    blitBuffer();
    return resultSerial;
  }

  template<typename T>
  size_t println(T const &value) {
    displayTimer = millis();
    state = STATE_INIT;

    // Forward to the underlying Serial
    size_t resultSerial = _serial.println(value);

    // Print the entire string onto the canvas
    size_t resultCanvas = _serialBufferCanvas.println(value);
    blitBuffer();
    return resultSerial;
  }

  // Overload for println without arguments.
  size_t println() {
    displayTimer = millis();
    state = STATE_INIT;

    size_t resultSerial = _serial.println();
    size_t resultCanvas = _serialBufferCanvas.println();
    blitBuffer();
    return resultSerial;
  }

  void blitBuffer() {
    int yPosition = _serialBufferCanvas.getCursorY();
    targetOffset = yPosition >= _serialCanvas.height() ? _serialCanvas.height() - yPosition : 0;

    targetOffset = max(targetOffset, -_serialBufferCanvas.height());

    deltaOffset = (int)ceil(8.0f / tweenFrames);

    updateCanvas();
  }

  void updateCanvas() {
    if (currentOffset != targetOffset) {
      state = STATE_INIT;
    }
    currentOffset -= deltaOffset;
    if (currentOffset < targetOffset) {
      currentOffset = targetOffset;
      deltaOffset = 0;
    }
    _serialCanvas.fillScreen(0);
    _serialCanvas.drawBitmap(0, currentOffset, _serialBufferCanvas.getBuffer(),
                             _serialCanvas.width(), _serialBufferCanvas.height(),
                             HX8357_WHITE);
  }

  // First, check our injected text buffer.
  int available() override {
    if (_injectedText.length() > 0) {
      return _injectedText.length();
    }
    return _serial.available();
  }

  // If there is injected text, return it first.
  int read() override {
    if (_injectedText.length() > 0) {
      char c = _injectedText.charAt(0);
      _injectedText.remove(0, 1);
      return c;
    }
    return _serial.read();
  }

  // Similarly, peek into the injected text first.
  int peek() override {
    if (_injectedText.length() > 0) {
      return _injectedText.charAt(0);
    }
    return _serial.peek();
  }

private:
  RenderState state;
  int currentRegion;
  int regionHeight;

  int currentOffset;
  int targetOffset;
  int deltaOffset;
  int tweenFrames;

  int bufferSize;
  unsigned long displayTimer;
  bool updateFlag = false;
  USBCDC &_serial;
  Adafruit_HX8357 &_tft;
  int _cursorX, _cursorY;
  String _injectedText;  // Buffer for injected text.
};

#endif  // SERIALWRAPPER_H