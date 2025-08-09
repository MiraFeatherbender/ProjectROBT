#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\CommandParser.h"
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
    CommandParser();
    void setNodeNumber(uint8_t NodeNumber);
    void getNodeNumber(uint8_t NodeNumber);
    void setDispatchCallback(CommandDispatchCallback cb);
    void parseAndDispatch(const String& inputLine, const CommandSourceContext& context);
private:
    uint8_t myNodeNumber;
    CommandDispatchCallback dispatchCallback;
    void parseParams(String& cmd, CommandType& type, std::vector<String>& params);
    void filterNodeParams(std::vector<String>& params, const String& nodeTag);

};
#endif // COMMANDPARSER_H
