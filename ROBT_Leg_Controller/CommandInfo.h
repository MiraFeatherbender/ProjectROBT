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
    Stopped,
    Moving,
    EStop,
    Maintenance,
    Updating
};

struct CommandInfo {
    CommandPriority priority;
    std::vector<SystemState> allowedStates;
    // Add more metadata fields as needed (e.g., description, usage)
};