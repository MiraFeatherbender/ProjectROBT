#ifndef ISTATEMACHINESTRATEGY_H
#define ISTATEMACHINESTRATEGY_H

#include <map>
#include <stdint.h>
#include "NodeData.h"

// Forward declaration of TrilaterationStateMachine to avoid circular dependencies
class TrilaterationStateMachine;

class IStateMachineStrategy {
public:
    virtual ~IStateMachineStrategy() {}

    // Handle state machine update
    virtual void updateStateMachine(TrilaterationStateMachine& stateMachine) = 0;

    // Handle data collection
    virtual void collectDataFromNode(TrilaterationStateMachine& stateMachine) = 0;

    // Handle prefiltering
    virtual void prefilterNodeData(TrilaterationStateMachine& stateMachine) = 0;

    // Handle command reception
    virtual void onCommandReceived(TrilaterationStateMachine& stateMachine, uint8_t nodeId, const ATResponseResult& res) = 0;
};

#endif  // ISTATEMACHINESTRATEGY_H
