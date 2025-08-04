#include <sys/_stdint.h>
#include "CommandParser.h"

CommandParser::CommandParser() {}

void CommandParser::setNodeNumber(uint8_t NodeNumber){
    myNodeNumber = NodeNumber;
}

void CommandParser::setDispatchCallback(CommandDispatchCallback cb) {
    dispatchCallback = cb;
}

void CommandParser::parseAndDispatch(const String& inputLine, const CommandSourceContext& context) {
    String cmd = inputLine;
    cmd.trim();
    if (cmd.length() == 0) return;
    uint8_t nodeNum = myNodeNumber;
    bool isBroadcast = false;
    if (cmd.startsWith("0 ")) {
        isBroadcast = true;
        int spaceIndex = cmd.indexOf(' ');
        if (spaceIndex == -1) return; // Invalid format
        cmd = cmd.substring(spaceIndex + 1);
        nodeNum = 0;
    }
    if (cmd.length() == 0) return;
    bool isOTA = cmd.equalsIgnoreCase("OTA");
    std::vector<String> params;
    CommandType type = CommandType::None;
    if (!isOTA) parseParams(cmd, type, params);
    if (isBroadcast) {
        filterNodeParams(params, "N" + String(myNodeNumber));
        if (params.empty()) return; // No payload for this node
    }
    if (!(isBroadcast || nodeNum == myNodeNumber)) return;
    ParsedCommand parsed{nodeNum, cmd, type, isOTA, params, context};
    if (dispatchCallback) dispatchCallback(parsed);
}

void CommandParser::parseParams(String& cmd, CommandType& type, std::vector<String>& params) {
    int plusIdx = cmd.indexOf('+');
    if (plusIdx != -1) {
        cmd = cmd.substring(plusIdx + 1);
    }
    int eqIdx = cmd.indexOf('=');
    int qIdx = cmd.indexOf('?');
    int tokenIdx = -1;

    if (eqIdx != -1 && (qIdx == -1 || eqIdx < qIdx)) {
        tokenIdx = eqIdx;
        type = CommandType::Set;
    } else if (qIdx != -1) {
        tokenIdx = qIdx;
        type = CommandType::Query;
    } else {
        // No valid command token found
        return;
    }

    String paramString = cmd.substring(tokenIdx + 1);
    while (paramString.length() > 0) {
        int commaIdx = paramString.indexOf(',');
        if (commaIdx == -1) {
            params.push_back(paramString);
            break;
        }
        params.push_back(paramString.substring(0, commaIdx));
        paramString = paramString.substring(commaIdx + 1);
    }
    // Now truncate cmd without token
    cmd = cmd.substring(0, tokenIdx);
}

/*
Example broadcast message for node 11:
  0 CMD=N5,100,200,|,N11,42,99,|,N7,77,88,|

After parseParams, params = ["N5", "100", "200", "|", "N11", "42", "99", "|", "N7", "77", "88", "|"]
Calling filterNodeParams(params, "N11") will result in params = ["42", "99"]
All other node blocks (N5, N7) are ignored for node 11.
*/
// Extracts only the parameters for this node from a broadcast params vector.
// Each node block starts with its tag (e.g., "N2") and ends with a standalone "|".
void CommandParser::filterNodeParams(std::vector<String>& params, const String& nodeTag) {
    std::vector<String> filtered;
    bool found = false;
    bool anyNodeTag = false;
    for (size_t i = 0; i < params.size(); ++i) {
        const String& p = params[i];
        if (p.length() > 1 && p[0] == 'N' && isdigit(p[1])) {
            anyNodeTag = true;
            if (p == nodeTag) {
                found = true;
                continue;
            } else if (found) {
                // If we were collecting and hit another node tag, stop
                break;
            }
        }
        if (found) {
            if (p == "|") break;
            filtered.push_back(p);
        }
    }
    if (anyNodeTag) {
        params = filtered; // Only replace if node tags were present
    }
}