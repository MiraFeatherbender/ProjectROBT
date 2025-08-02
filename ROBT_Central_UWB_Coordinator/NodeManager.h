#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <Arduino.h>
#include <vector>
#include "OuterNode.h"
#include "ESPNowHandler.h"

class NodeManager {
private:
  std::vector<std::unique_ptr<OuterNode>> nodes;  // Collection of node objects.
  ESPNowHandler* comms;                           // Pointer to the ESPNowHandler.

public:
  NodeManager(ESPNowHandler* handler);
  ~NodeManager();

  // Add a new node.
  void addNode(std::unique_ptr<OuterNode> node);

  // Process serial input; returns true if a valid command is parsed.
  // The expected format is: "<nodeNumber> <AT command>"
  bool processSerialInput(String& cmd, uint8_t& targetNodeNumber);

  // Dispatch the command: if node number is 0, broadcast.
  // For unicast, find the node and let it handle its own command.
  void dispatchCommand(const String& cmd, uint8_t targetNodeNumber);

  // Called by the ESPNowHandler external callback.
  void handleIncomingMessage(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len);

  // Optional: Check timeouts for each node (if nodes maintain status).
  void checkTimeouts(unsigned long ackTimeout, unsigned long responseTimeout);

  // Helper: find a node by its number.
  OuterNode* findNodeByNumber(uint8_t nodeNumber);

  // Initializes all nodes: registers peers and then initializes each node.
  void initializeNodes();

  // Registers response callbacks for code to know when command responses arrive.
  void registerCallbacks();

  // Public getter for finding nodes that default to UWB Anchors
  std::vector<uint8_t> getAnchorNodeNumbers() const;
};

#endif  // NODEMANAGER_H
