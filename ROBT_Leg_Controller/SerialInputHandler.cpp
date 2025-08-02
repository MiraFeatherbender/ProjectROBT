#include "SerialInputHandler.h"

SerialInputHandler::SerialInputHandler() : buffer("") {}

void SerialInputHandler::begin(unsigned long baud) {
    Serial.begin(baud);
}

void SerialInputHandler::setLineCallback(SerialLineCallback cb) {
    lineCallback = cb;
}

void SerialInputHandler::update() {
    while (Serial.available() > 0) {
        String line = Serial.readStringUntil('\n');
        line.trim(); // Removes leading/trailing whitespace, including '\r'
        if (line.length() > 0 && lineCallback) {
            CommandSourceContext ctx;
            ctx.source = CommandSourceContext::SERIAL;
            ctx.respond = [](const String& resp) { Serial.println(resp); };
            lineCallback(line, ctx);
        }
    }
}
