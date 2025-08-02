#ifndef STATEMACHINESTRATEGYBASE_H
#define STATEMACHINESTRATEGYBASE_H

// #include "TrilaterationEngine.h"
// #include "TrilaterationStateMachine.h"
#include "IStateMachineStrategy.h"
#include "NodeManager.h"

// Forward declaration of TrilaterationStateMachine to avoid circular dependencies
class TrilaterationStateMachine;

extern NodeManager nodeManager;

class StateMachineStrategyBase : public IStateMachineStrategy {
protected:
  void processCompletedNodes(TrilaterationStateMachine& stateMachine) {
    stateMachine.enqueueSnapshot();
    switch (stateMachine.getCurrentMode()) {
      case Mode::FREERUN:
        break;
      default:
        stateMachine.updateModeToInactive();
        break;
    }
    stateMachine.processSnapshots();
  }

  // Shared helper for processing node data
  void processNodeData(TrilaterationStateMachine& stateMachine, uint8_t nodeId,
                       const String& commandToken, const String& commandToSend, NodeState nextState) {

    stateMachine.registerStateMachineCallback(nodeId, commandToken);

    OuterNode* node = nodeManager.findNodeByNumber(nodeId);
    if (node) {
      node->sendCommand(commandToSend);
      stateMachine.nodeDataMap[nodeId].state = nextState;
    }
  }

public:
  virtual ~StateMachineStrategyBase() {}
};

#endif  // STATEMACHINESTRATEGYBASE_H
