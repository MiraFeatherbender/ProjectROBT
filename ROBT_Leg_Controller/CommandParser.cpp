#include "CommandParser.h"

CommandParser::CommandParser(uint8_t myNodeNumber) : myNodeNumber(myNodeNumber) {}

void CommandParser::setDispatchCallback(CommandDispatchCallback cb) {
    dispatchCallback = cb;
}

void CommandParser::parseAndDispatch(const String& inputLine, const CommandSourceContext& context) {
    String line = inputLine;
    line.trim();
    int spaceIndex = line.indexOf(' ');
    if (spaceIndex == -1) return; // Invalid format
    String nodeNumStr = line.substring(0, spaceIndex);
    String cmd = line.substring(spaceIndex + 1);
    cmd.trim();
    if (nodeNumStr.length() == 0 || cmd.length() == 0) return;
    uint8_t nodeNum = nodeNumStr.toInt();
    bool isBroadcast = (nodeNum == 0);
    bool isOTA = cmd.equalsIgnoreCase("OTA");
    std::vector<String> params;
    if (!isOTA) parseParams(cmd, params);
    // Only dispatch if this node or broadcast
    if (isBroadcast || nodeNum == myNodeNumber) {
        ParsedCommand parsed{nodeNum, cmd, isOTA, params, context};
        if (dispatchCallback) dispatchCallback(parsed);
    }
}

void CommandParser::parseParams(const String& cmd, std::vector<String>& params) {
    int eqIdx = cmd.indexOf('=');
    if (eqIdx == -1) return;
    String paramString = cmd.substring(eqIdx + 1);
    while (paramString.length() > 0) {
        int commaIdx = paramString.indexOf(',');
        if (commaIdx == -1) {
            params.push_back(paramString);
            break;
        }
        params.push_back(paramString.substring(0, commaIdx));
        paramString = paramString.substring(commaIdx + 1);
    }
}
