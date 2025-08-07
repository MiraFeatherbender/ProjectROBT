#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\CommandInfo.h"

#pragma once
#include <vector>

enum class CommandPriority {
    PriorityLow,
    PriorityNormal,
    PriorityHigh,
    PriorityCritical
};

enum class SystemState {
    Booting,
    Parked,
    Homed,
    Stopped,
    ProcessMoveCmd,
    Moving,
    EStop,
    Maintenance,
    Calibrating,
    Updating
};

// Structure representing a state transition for LegSupervisor
struct StateTransition {
    SystemState nextState;
    std::vector<float> params; // Parameters for the transition (e.g., steering, velocity, slew)
    StateTransition(SystemState state, std::vector<float> p = std::vector<float>()) : nextState(state), params(std::move(p)) {}
};

struct CommandInfo {
    CommandPriority priority;
    std::vector<SystemState> allowedStates;
    // Add more metadata fields as needed (e.g., description, usage)
};