#ifndef PARSED_COMMAND_H
#define PARSED_COMMAND_H

#include <Arduino.h>
#include <vector>
#include "SerialInputHandler.h" // For CommandSourceContext

struct ParsedCommand {
    uint8_t nodeNumber;
    String command;
    bool isOTA;
    std::vector<String> params;
    CommandSourceContext context; // Source and response callback
};

#endif // PARSED_COMMAND_H