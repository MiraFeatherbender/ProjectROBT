#include "OuterNode.h"
#include "ESPNowHandler.h"
#include "TrilaterationEngine.h"

// Assume a global instance of ESPNowHandler is declared in the central node sketch
extern ESPNowHandler espHandler;

OuterNode::OuterNode(uint8_t nodeNum, const uint8_t *mac, NodeType nodeType, const ATCommandMap &defaultMap)
  : nodeNumber(nodeNum), type(nodeType), atStateManager(defaultMap),  // pass defaultMap here
    waitingForAck(false), waitingForResponse(false), active(true), startTime(0) {
  memcpy(macAddress, mac, 6);
}

OuterNode::~OuterNode() {
}

void OuterNode::initialize() {
  // First, query all commands to refresh the dynamic state.
  // Assuming that getDynamicState() returns all known command tokens.
  std::set<String> tokensToSkip = getTokensToSkip();

  for (const auto &entry : atStateManager.getDynamicState()) {
    if (tokensToSkip.find(entry.first) != tokensToSkip.end()) {
      continue;
    }
    sendQuery(entry.first);
    // Give the node a bit of time for responses (if needed)
    delay(20);
  }

  // Next, enforce defaults by comparing the dynamic state to the static definitions
  // and the subclass overrides.
  synchronizeSettings();
}

void OuterNode::synchronizeSettings() {
  // Get a copy of the current dynamic state.
  const auto &dynamicMap = atStateManager.getDynamicState();

  // Build a set of tokens to skip. For example, tokens that shouldn't be compared.
  std::set<String> tokensToSkip = getTokensToSkip();  // Assuming you have this function.

  for (const auto &pair : dynamicMap) {
    const String &token = pair.first;

    // Skip tokens that are in the skip list.
    if (tokensToSkip.find(token) != tokensToSkip.end()) {
      continue;
    }

    const String &currentValue = pair.second;
    // Use the modular helper to figure out the final expected value.
    String expectedValue = determineExpectedValue(token, currentValue);

    if (currentValue != expectedValue) {
      String setCmd = ATCommandStateManager::buildSetCommand(token, expectedValue);
      sendCommand(setCmd);

      String synched = "Synchronizing " + token + ": current = " + currentValue + ", setting to = " + expectedValue;
      Serial.println(synched);
    }
  }
}

String OuterNode::determineExpectedValue(const String &token, const String &currentValue) const {
  String expectedValue = currentValue;  // default to the current value

  // Check static default from ATCommandStateManager.
  auto defIt = atStateManager.getDefaultDefinitions().find(token);
  if (defIt != atStateManager.getDefaultDefinitions().end() && defIt->second.defaultValue != "") {
    expectedValue = defIt->second.defaultValue;
  }

  // Override with node-specific default if available.
  auto nodeDefaults = getPerNodeDefaultSettings();
  auto nodeDefaultIt = nodeDefaults.find(token);
  if (nodeDefaultIt != nodeDefaults.end()) {
    expectedValue = nodeDefaultIt->second;
  }

  return expectedValue;
}

bool OuterNode::sendCommand(const String &cmd) {
  // Example implementation:
  uint8_t commandType = CMD_STANDARD;
  if (cmd.equalsIgnoreCase("OTA")) {
    commandType = CMD_OTA;
  }

  uint8_t message[251];
  // For unicast, the first byte (broadcast flag) is 0.
  message[0] = 0;
  message[1] = commandType;

  int payloadLength = 0;
  if (commandType == CMD_STANDARD) {
    payloadLength = cmd.length();
    memcpy(&message[2], cmd.c_str(), payloadLength);
  }
  int totalLength = (commandType == CMD_STANDARD) ? payloadLength + 2 : 2;


  // Assume espHandler is accessible.
  bool result = espHandler.sendMessage(getMAC(), message, totalLength);
  if (result) {
    waitingForAck = true;
    startTime = millis();
  }
  return result;
}

void OuterNode::handleResponse(const String &response) {
  ATResponseResult res = atStateManager.updateFromResponse(response);

  if (response.equals("ACK")) {
    waitingForAck = false;
    waitingForResponse = true;
    return;
  }

  waitingForResponse = false;

  // Trigger the callback with the entire response result object
  if (onResponseCallback) {
    onResponseCallback(res);  // Pass the ATResponseResult object
  }

  Mode currentMode;
  if(xQueuePeek(TrilaterationEngine::getInstance().getModeQueue(), &currentMode, 0) == pdPASS && currentMode != Mode::INACTIVE){
    return;
  }

  // Mode currentMode;
  // if (xQueuePeek(TrilaterationManager::getInstance().getModeQueue(), &currentMode, 0) == pdPASS && currentMode != Mode::INACTIVE) {
  //   return;
  // }

  if (res.updated) {
    Serial.printf("%d %s updated: %s\n", nodeNumber, res.commandToken.c_str(), res.convertedParameter.c_str());
    return;
  }

  Serial.printf("%d %s", nodeNumber, response.c_str());
}

void OuterNode::sendQuery(const String &cmd) {
  String query = atStateManager.buildQueryCommand(cmd);
  sendCommand(query);
}

uint8_t OuterNode::getNodeNumber() const {
  return nodeNumber;
}
const uint8_t *OuterNode::getMAC() const {
  return macAddress;
}
NodeType OuterNode::getType() const {
  return type;
}
bool OuterNode::isActive() const {
  return active;
}
bool OuterNode::isWaitingForAck() const {
  return waitingForAck;
}
bool OuterNode::isWaitingForResponse() const {
  return waitingForResponse;
}
unsigned long OuterNode::getStartTime() const {
  return startTime;
}

void OuterNode::setWaitingForAck(bool status) {
  waitingForAck = status;
}
void OuterNode::setWaitingForResponse(bool status) {
  waitingForResponse = status;
}
void OuterNode::setStartTime(unsigned long t) {
  startTime = t;
}
