#ifndef DIRECTIONFINDINGSTRATEGY_H
#define DIRECTIONFINDINGSTRATEGY_H

// #include "TrilaterationStateMachine.h"
#include "StateMachineStrategyBase.h"
#include "Mode.h"
#include "NodeData.h"

class TrilaterationStateMachine;

class DirectionFindingStrategy : public StateMachineStrategyBase {
public:
  void updateStateMachine(TrilaterationStateMachine& stateMachine) override {
    if (std::all_of(stateMachine.nodeDataMap.begin(), stateMachine.nodeDataMap.end(), [](const auto& pair) {
          return pair.second.state == NodeState::COMPLETE;
        })) {
      Serial.println("\nAll nodes have completed their tasks!");
      processCompletedNodes(stateMachine);  // Call the base class helper for shared logic
    }
  }

  void collectDataFromNode(TrilaterationStateMachine& stateMachine) override {
    for (auto& [nodeId, data] : stateMachine.nodeDataMap) {
      if (data.state != NodeState::WAITING_FOR_MEAS) {
        continue;
      }
      processNodeData(stateMachine, nodeId, "MEAS_DISTANCE", "AT+MEAS_DISTANCE=1,10", NodeState::WAITING_FOR_MEAS_RESPONSE);
      stateMachine.collectState = CollectState::WAIT;
      break;
    }
  }

  void prefilterNodeData(TrilaterationStateMachine& stateMachine) override {
    for (auto& [nodeId, data] : stateMachine.nodeDataMap) {
      if (data.state != NodeState::WAITING_FOR_READ) {
        continue;
      }
      processNodeData(stateMachine, nodeId, "READ_DISTANCE", "AT+READ_DISTANCE", NodeState::WAITING_FOR_READ_RESPONSE);
      stateMachine.prefilterState = PrefilterState::WAIT;
      break;
    }
  }

  void onCommandReceived(TrilaterationStateMachine& stateMachine, uint8_t nodeId, const ATResponseResult& res) override {
    if (res.commandToken == "MEAS_DISTANCE") {
      stateMachine.nodeDataMap[nodeId].state = NodeState::WAITING_FOR_READ;
      stateMachine.activeNode = -1;
      stateMachine.collectState = CollectState::COLLECT;
    } else if (res.commandToken == "READ_DISTANCE") {
      stateMachine.nodeDataMap[nodeId].state = NodeState::COMPLETE;
      stateMachine.nodeDataMap[nodeId].distance = res.convertedParameter.toInt();
      stateMachine.prefilterState = PrefilterState::PREFILTER;
    }
  }
};

#endif  // DIRECTIONFINDINGSTRATEGY_H
