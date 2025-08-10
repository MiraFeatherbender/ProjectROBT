#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\CommandInfo.h"
#pragma once
#include <vector>
#include <map>
#include <string>

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

// Map SystemState enum to plain text
static const std::map<SystemState, std::string> SystemStateText = {
    {SystemState::Booting,      "BOOTING"},
    {SystemState::Parked,       "PARKED"},
    {SystemState::Homed,        "HOMED"},
    {SystemState::Stopped,      "STOPPED"},
    {SystemState::ProcessMoveCmd,"PROCESS_MOVE_CMD"},
    {SystemState::Moving,       "MOVING"},
    {SystemState::EStop,        "E_STOP"},
    {SystemState::Maintenance,  "MAINTENANCE"},
    {SystemState::Calibrating,  "CALIBRATING"},
    {SystemState::Updating,     "UPDATING"}
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