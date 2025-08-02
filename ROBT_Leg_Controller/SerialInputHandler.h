#ifndef SERIALINPUTHANDLER_H
#define SERIALINPUTHANDLER_H
#include <Arduino.h>
#include <functional>
#include <string>

struct CommandSourceContext {
    enum SourceType { SERIAL, ESP_NOW } source;
    std::function<void(const String&)> respond;
};

// Callback type for passing received lines and context to the parser
using SerialLineCallback = std::function<void(const String&, const CommandSourceContext&)>;

class SerialInputHandler {
public:
    SerialInputHandler();
    void begin(unsigned long baud = 115200);
    void update();
    void setLineCallback(SerialLineCallback cb);
private:
    String buffer;
    SerialLineCallback lineCallback;
};
#endif // SERIALINPUTHANDLER_H
