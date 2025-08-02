#ifndef TRILATERATIONSTATEMACHINE_H
#define TRILATERATIONSTATEMACHINE_H

#include <Arduino.h>
#include <algorithm>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <map>
#include "Mode.h"
#include "NodeData.h"
#include "NodeManager.h"
#include "IStateMachineStrategy.h"

extern NodeManager nodeManager;

class TrilaterationStateMachine {
private:
  QueueHandle_t snapshotQueue;

  // Strategy pointer
  IStateMachineStrategy* stateStrategy = nullptr;

  // Parallel state machines for UWB data
  void handleDataCollection();
  void handlePrefiltering();

  // Helper methods for DataCollection
  void initializeDataCollection();

  // Helper methods for Prefiltering
  void initializePrefiltering();

public:
  explicit TrilaterationStateMachine(QueueHandle_t queue)
    : snapshotQueue(queue),
      collectState(CollectState::INIT),
      prefilterState(PrefilterState::INIT) {}

  std::map<uint8_t, NodeData> nodeDataMap;
  CollectState collectState;
  PrefilterState prefilterState;
  int activeNode;

  Mode getCurrentMode() const;
  void updateModeToInactive();

  void registerStateMachineCallback(uint8_t nodeId, const String& expectedCommand);  // Callback registrar for state machines

  void enqueueSnapshot();   // Enqueue snapshot of nodeDataMap
  void processSnapshots();  // Dequeue snapshot and print to console

  // Assign a strategy
  void setStateStrategy(IStateMachineStrategy* strategy) {
    stateStrategy = strategy;
  }

  // Delegate to strategy
  void updateStateMachine() {
    handleDataCollection();  // Common logic
    handlePrefiltering();    // Common logic
    if (stateStrategy) {
      stateStrategy->updateStateMachine(*this);  // Delegate strategy-specific behavior
    }
  }

  void collectDataFromNode() {
    if (stateStrategy) {
      stateStrategy->collectDataFromNode(*this);
    }
  }
  void prefilterNodeData() {
    if (stateStrategy) {
      stateStrategy->prefilterNodeData(*this);
    }
  }
  void onCommandReceived(uint8_t nodeId, const ATResponseResult& res) {
    if (stateStrategy) {
      stateStrategy->onCommandReceived(*this, nodeId, res);
    }
  }

  void buildAnchorMap();
};

#endif  //TRILATERATIONSTATEMACHINE_H