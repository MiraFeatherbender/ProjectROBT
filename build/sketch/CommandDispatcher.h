#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\CommandDispatcher.h"
#pragma once
#include <map>
#include <functional>
#include <string>
#include "ParsedCommand.h"
#include "CommandInfo.h" // <-- Include your new metadata struct
#include "LegSupervisor.h" // <-- Fix: Add missing declaration for LegSupervisor

// Flexible dispatcher for AT commands

class CommandDispatcher {
public:
    using Handler = std::function<void(const ParsedCommand&)>;

    struct RegisteredCommand {
        Handler handler;
        CommandInfo info;
    };

    // Register a handler and metadata for a command string
    void registerCommand(const std::string& cmd, Handler handler, const CommandInfo& info);

    // Clear all handlers (for test or re-init)
    void clear();

    // Check if a command is allowed in the current state/priority
    bool isAllowed(const CommandInfo& info, SystemState currentState, CommandPriority currentPriority) const;

    // Dispatch a command, using LegSupervisor for state/priority/queue
    bool dispatch(const ParsedCommand& cmd, LegSupervisor& supervisor) const;

    // Access command metadata (for validation, docs, etc.)
    const CommandInfo* getCommandInfo(const std::string& cmd) const;

private:
    std::map<std::string, RegisteredCommand> commands_;
};
