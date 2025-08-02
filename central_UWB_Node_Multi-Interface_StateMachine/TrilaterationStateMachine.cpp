#include "TrilaterationStateMachine.h"
#include "TrilaterationEngine.h"

void TrilaterationStateMachine::handleDataCollection() {
  switch (collectState) {
    case CollectState::INIT:
      initializeDataCollection();
      break;
    case CollectState::COLLECT:
      collectDataFromNode();
      break;
    case CollectState::WAIT:
      break;
  }
}

void TrilaterationStateMachine::handlePrefiltering() {
  switch (prefilterState) {
    case PrefilterState::INIT:
      initializePrefiltering();
      break;
    case PrefilterState::PREFILTER:
      prefilterNodeData();
      break;
    case PrefilterState::WAIT:
      break;
  }
}

void TrilaterationStateMachine::initializeDataCollection() {
  activeNode = -1;  // Clear active node
  collectState = CollectState::COLLECT;
  for (auto& [nodeId, data] : nodeDataMap) {
    if (data.state == NodeState::WAITING_FOR_MEAS) {
      continue;  // Skip nodes that don't match the condition
    }
    data.state = NodeState::WAITING_FOR_MEAS;
  }
}

void TrilaterationStateMachine::initializePrefiltering() {
  prefilterState = PrefilterState::PREFILTER;
}

void TrilaterationStateMachine::registerStateMachineCallback(uint8_t nodeId, const String& expectedCommand) {
  OuterNode* node = nodeManager.findNodeByNumber(nodeId);
  if (!node) {
    Serial.printf("Node %d not found!\n", nodeId);
    return;
  }

  // Register the callback
  node->setResponseCallback([this, nodeId, expectedCommand](const ATResponseResult& res) {
    if (res.commandToken == expectedCommand) {
      onCommandReceived(nodeId, res);  // Notify the state machine, passing the full result
    }
  });
}

void TrilaterationStateMachine::enqueueSnapshot() {
  // Create a new map to hold the snapshot
  std::shared_ptr<std::map<uint8_t, NodeData>> mapSnapshot = std::make_shared<std::map<uint8_t, NodeData>>(nodeDataMap);
  // Push the snapshot to the queue
  if (xQueueSend(snapshotQueue, &mapSnapshot, 0) != pdPASS) {
    Serial.println("Snapshot queue is full, could not enqueue snapshot.");
  }
  collectState = CollectState::INIT;
  prefilterState = PrefilterState::INIT;
}

void TrilaterationStateMachine::processSnapshots() {
  std::shared_ptr<std::map<uint8_t, NodeData>> mapSnapshot;
  // Wait for a snapshot to be available
  if (xQueueReceive(snapshotQueue, &mapSnapshot, portMAX_DELAY) == pdPASS) {
    // Process the mapSnapshot (e.g., feed it into the direction-finding algorithm)
    Serial.println("Snapshot ready for direction finding.");
    // performDirectionFinding(*mapSnapshot);
    for (const auto& [nodeId, data] : *mapSnapshot) {
      Serial.printf("Node ID: %d, Distance: %d\n", nodeId, data.distance);
    }
  }
}

void TrilaterationStateMachine::buildAnchorMap() {
  // Dynamically populate nodeStates based on Anchor nodes
  for (uint8_t nodeId : nodeManager.getAnchorNodeNumbers()) {
    nodeDataMap[nodeId] = NodeData{ 0, 0, NodeState::WAITING_FOR_MEAS, 0 };
  }
}

Mode TrilaterationStateMachine::getCurrentMode() const {
  return TrilaterationEngine::getInstance().getMode();
}

void TrilaterationStateMachine::updateModeToInactive() {
  TrilaterationEngine::getInstance().setMode("INACTIVE");
}
