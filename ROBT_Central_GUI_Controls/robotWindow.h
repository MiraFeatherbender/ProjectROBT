#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include <SdFat.h>
#include <Adafruit_ImageReader.h>

class robotWindow {
public:
  robotWindow(Adafruit_HX8357 &tft, GFXcanvas16 &robotCanvas, Adafruit_ImageReader &reader)
    : _tft(tft), _robotCanvas(robotCanvas), _reader(reader) {
  }

  enum sensorStatus{
    INACTIVE = 0,
    SENDING = 1,
    RECEIVING = 2
  };


  struct Sensor{
    int x, y;
    sensorStatus status;
    bool isDirty;
  };

  std::array<Sensor, 5> sensors;
  
  void draw() {
    for(auto &sensor : sensors){
      if(sensor.isDirty){
        drawSensorStatus(sensor);
        sensor.isDirty = false;
      }
    }
  }

  void begin() {
    _reader.loadBMP("/Frame.bmp", frame);
    _reader.loadBMP("/SLNTSNSR.bmp", inactive);
    _reader.loadBMP("/SNDSNSR.bmp", send);
    _reader.loadBMP("/RCVSNSR.bmp", receive);
    sensorFactory();
    frame.draw(_tft, 0, 0);
  }

  void setSensorStatus(int sensorID, sensorStatus newStatus){
    if(sensorID < 0 || sensorID >= sensors.size()){
      return;
    }
    if(sensors[sensorID].status == newStatus){
      return;
    }
    sensors[sensorID].status = newStatus;
    sensors[sensorID].isDirty = true;
  }

  sensorStatus getSensorStatus(int sensorID){
    return sensors[sensorID].status;
  }

private:
  Adafruit_HX8357 &_tft;
  GFXcanvas16 &_robotCanvas;

  Adafruit_ImageReader _reader;

  Adafruit_Image frame;

  Adafruit_Image inactive;
  Adafruit_Image send;
  Adafruit_Image receive;

  const int virtualOriginX = 150;
  const int virtualOriginY = 100;


  void sensorFactory() {
    int xOffset = 132;
    int yOffset = 82;

    // Initialize sensors with placeholders.
    sensors[0] = Sensor{-1, 1, INACTIVE, true};
    sensors[1] = Sensor{-1, -1, INACTIVE, true};
    sensors[2] = Sensor{0, 0, INACTIVE, true};
    sensors[3] = Sensor{1, -1, INACTIVE, true};
    sensors[4] = Sensor{1, 1, INACTIVE, true};

    // Apply offsets and finalize setup.
    for (auto &sensor : sensors) {
      sensor.x *= xOffset;
      sensor.y *= yOffset;
    }
  }

  void drawSensorStatus(const Sensor &sensor){
    Adafruit_Image*imageToDraw = nullptr;
    switch (sensor.status){
      case SENDING:
        imageToDraw = &send;
        break;
      case RECEIVING:
        imageToDraw = &receive;
        break;
      default:
        imageToDraw = &inactive;
        break;
    }

    imageToDraw->draw(_tft, sensor.x + virtualOriginX, sensor.y + virtualOriginY);
  }
};

#endif  //ROBOTWINDOW_H