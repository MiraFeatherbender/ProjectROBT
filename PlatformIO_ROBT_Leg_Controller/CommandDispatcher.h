
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
    void registerCommand(const std::string& cmd, Handler handler, const CommandInfo& info) {
        commands_[cmd] = RegisteredCommand{handler, info};
    }

    // Add this method to check if a command is allowed
    bool isAllowed(const CommandInfo& info, SystemState currentState, CommandPriority currentPriority) const {
        // CRITICAL commands are always allowed and should trigger queue override
        if (info.priority == CommandPriority::PriorityCritical) {
            // In your main dispatch logic, you should clear the transition queue before handling
            return true;
        }
        for (auto allowed : info.allowedStates) {
            if (allowed == currentState) {
                return info.priority >= currentPriority;
            }
        }
        return false;
    }

    // Refactored dispatch method to use LegSupervisor for state, priority, and queue clearing
    // Returns true if a handler was found and called, false otherwise
    bool dispatch(const ParsedCommand& cmd, LegSupervisor& supervisor) const {
        const auto& reg = commands_.at(std::string(cmd.command.c_str()));
        SystemState currentState = supervisor.getCurrentState();
        CommandPriority currentPriority = supervisor.getCurrentPriority();
        if (isAllowed(reg.info, currentState, currentPriority)) {
            // Clear transition queue for equal or higher priority commands
            if (reg.info.priority >= currentPriority) {
                supervisor.clearTransitionQueue();
            }
            reg.handler(cmd);
            return true;
        }
        return false;
    }

    // Optional: Access command metadata (for validation, docs, etc.)
    const CommandInfo* getCommandInfo(const std::string& cmd) const {
        auto it = commands_.find(cmd);
        if (it != commands_.end()) {
            return &it->second.info;
        }
        return nullptr;
    }

    // Optional: clear all handlers (for test or re-init)
    void clear() { commands_.clear(); }

/*
Example usage:

CommandDispatcher dispatcher;
dispatcher.registerCommand("MOVE", [&](const ParsedCommand& cmd) {
    supervisor.move(cmd.params);
}, CommandInfo{"Move the device", "param1,param2"});
dispatcher.registerCommand("NVSDIAG", [&](const ParsedCommand& cmd) {
    nvsManager.diagnostic(cmd.params);
}, CommandInfo{"Diagnostic information", "param1"});

// In your parser's dispatch callback:
if (!dispatcher.dispatch(cmd, supervisor)) {
    // Handle unknown command
}
*/

private:
    std::map<std::string, RegisteredCommand> commands_;
};

/*
Example usage:

CommandDispatcher dispatcher;
dispatcher.registerCommand("MOVE", [&](const ParsedCommand& cmd) {
    supervisor.move(cmd.params);
}, CommandInfo{"Move the device", "param1,param2"});
dispatcher.registerCommand("NVSDIAG", [&](const ParsedCommand& cmd) {
    nvsManager.diagnostic(cmd.params);
}, CommandInfo{"Diagnostic information", "param1"});

// In your parser's dispatch callback:
if (!dispatcher.dispatch(cmd)) {
    // Handle unknown command
}
*/
