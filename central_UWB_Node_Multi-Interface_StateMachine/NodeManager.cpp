#include "NodeManager.h"
#include "NodeFactory.h"

// You might later include other node type headers.

NodeManager::NodeManager(ESPNowHandler* handler)
  : comms(handler) {}

NodeManager::~NodeManager() = default;

void NodeManager::addNode(std::unique_ptr<OuterNode> node) {
  nodes.push_back(std::move(node));
}

bool NodeManager::processSerialInput(String& cmd, uint8_t& targetNodeNumber) {
  if (Serial.available() > 0) {
    String inputLine = Serial.readStringUntil('\n');
    inputLine.trim();
    int spaceIndex = inputLine.indexOf(' ');
    if (spaceIndex == -1) {  // No space found → invalid format.
      Serial.println("Invalid input. Use: <nodeNumber> <AT command>");
      return false;
    }
    String nodeNumStr = inputLine.substring(0, spaceIndex);
    cmd = inputLine.substring(spaceIndex + 1);
    cmd.trim();
    if (nodeNumStr.length() == 0 || cmd.length() == 0) {
      Serial.println("Invalid input. Both nodeNumber and command are required.");
      return false;
    }
    targetNodeNumber = nodeNumStr.toInt();
    return true;
  }
  return false;
}

void NodeManager::dispatchCommand(const String& cmd, uint8_t targetNodeNumber) {
  uint8_t commandType = CMD_STANDARD;
  if (cmd.equalsIgnoreCase("OTA")) {
    commandType = CMD_OTA;
  }

  uint8_t message[250];
  message[0] = (targetNodeNumber == 0) ? 1 : 0;
  message[1] = commandType;

  int payloadLength = 0;
  if (commandType == CMD_STANDARD) {
    payloadLength = cmd.length();
    memcpy(&message[2], cmd.c_str(), payloadLength);
  }
  int totalLength = (commandType == CMD_STANDARD) ? payloadLength + 2 : 2;

  if (targetNodeNumber == 0) {
    // Broadcast message.
    comms->sendMessage(nullptr, message, totalLength);
  } else {
    OuterNode* node = findNodeByNumber(targetNodeNumber);
    if (node) {
      node->sendCommand(cmd);
    } else {
      Serial.println("Node not found for unicast command.");
    }
  }
}

void NodeManager::handleIncomingMessage(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len) {
  char receivedData[250] = { 0 };
  int copyLen = (data_len < 249) ? data_len : 249;
  memcpy(receivedData, data, copyLen);
  receivedData[copyLen] = '\0';

  // Match node using MAC address.
  for (const auto& node : nodes) {  // `auto&` refers to the `std::unique_ptr<OuterNode>`.
    if (memcmp(node->getMAC(), recv_info->src_addr, 6) == 0) {
      node->handleResponse(String(receivedData));
      return;
    }
  }

  Serial.println("Received data from unknown node.");
}

void NodeManager::checkTimeouts(unsigned long ackTimeout, unsigned long responseTimeout) {
  // Do timeout processing for each node, if needed.
}

OuterNode* NodeManager::findNodeByNumber(uint8_t nodeNumber) {
  for (const auto& node : nodes) {  // Use `const auto&` to iterate over `std::unique_ptr`.
    if (node->getNodeNumber() == nodeNumber) {
      return node.get();  // Access the raw pointer for returning.
    }
  }
  return nullptr;
}


void NodeManager::initializeNodes() {
  auto nodesFromFactory = NodeFactory::createNodes();

  for (auto& node : nodesFromFactory) {
    comms->addPeer(node->getMAC());
    // Transfer ownership of the node to the NodeManager.
    nodes.push_back(std::move(node));
  }
  delay(1500);
  for (auto& node : nodes) {
    node->initialize();
  }
}

std::vector<uint8_t> NodeManager::getAnchorNodeNumbers() const {
  std::vector<uint8_t> anchorNodes;
  for (const auto& node : nodes) {
    if (node->isAnchor()) {  // Polymorphic call
      anchorNodes.push_back(node->getNodeNumber());
    }
  }
  return anchorNodes;
}
