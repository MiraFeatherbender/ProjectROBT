#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <Arduino.h>
#include <vector>
#include <functional>
#include "SerialInputHandler.h" // For CommandSourceContext

struct ParsedCommand {
    uint8_t nodeNumber;
    String command;
    bool isOTA;
    std::vector<String> params;
    CommandSourceContext context; // Source and response callback
};

// Callback type for dispatching parsed commands
using CommandDispatchCallback = std::function<void(const ParsedCommand&)>;

class CommandParser {
public:
    CommandParser(uint8_t myNodeNumber);
    void setDispatchCallback(CommandDispatchCallback cb);
    void parseAndDispatch(const String& inputLine, const CommandSourceContext& context);
private:
    uint8_t myNodeNumber;
    CommandDispatchCallback dispatchCallback;
    void parseParams(const String& cmd, std::vector<String>& params);
};
#endif // COMMANDPARSER_H
