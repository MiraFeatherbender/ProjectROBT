#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\SerialInputHandler.cpp"
#include "SerialInputHandler.h"

SerialInputHandler::SerialInputHandler() : buffer("") {}

void SerialInputHandler::begin(unsigned long baud) {
    Serial.begin(baud);
    Serial.println("Test");
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
            ctx.source = CommandSourceContext::serial_;
            ctx.respond = [](const String& resp) { Serial.println(resp); };
            lineCallback(line, ctx);
        }
    }
}
