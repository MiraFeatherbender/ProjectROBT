#pragma once
#include <vector>

enum class CommandPriority {
    LOW,
    NORMAL,
    HIGH,
    CRITICAL
};

enum class SystemState {
    Booting,
    Parked,
    Homed,
    Stopped,
    Moving,
    EStop,
    Maintenance,
    Calibrating,
    Updating
};

struct CommandInfo {
    CommandPriority priority;
    std::vector<SystemState> allowedStates;
    // Add more metadata fields as needed (e.g., description, usage)
};