#ifndef PARSED_COMMAND_H
#define PARSED_COMMAND_H

#include <Arduino.h>
#include <vector>
#include "SerialInputHandler.h" // For CommandSourceContext

enum class CommandType {None, Set, Query};

struct ParsedCommand {
    uint8_t nodeNumber;
    String command;
    CommandType type;
    bool isOTA;
    std::vector<String> params;
    CommandSourceContext context; // Source and response callback
};

#endif // PARSED_COMMAND_H