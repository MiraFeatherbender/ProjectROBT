#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <Arduino.h>
#include <vector>
#include <functional>
#include "SerialInputHandler.h" // For CommandSourceContext
#include "ParsedCommand.h" // For ParsedCommand

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
