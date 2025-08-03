#pragma once
#include <map>
#include <functional>
#include <string>
#include "ParsedCommand.h" // Assumes you have a struct ParsedCommand

// Flexible dispatcher for AT commands
class CommandDispatcher {
public:
    using Handler = std::function<void(const ParsedCommand&)>;

    // Register a handler for a command string (e.g., "MOVE")
    void registerCommand(const std::string& cmd, Handler handler) {
        handlers_[cmd] = handler;
    }

    // Dispatch a parsed command to the appropriate handler
    // Returns true if a handler was found and called, false otherwise
    bool dispatch(const ParsedCommand& cmd) const {
        auto it = handlers_.find(std::string(cmd.command.c_str()));
        if (it != handlers_.end()) {
            it->second(cmd);
            return true;
        }
        return false;
    }

    // Optional: clear all handlers (for test or re-init)
    void clear() { handlers_.clear(); }

private:
    std::map<std::string, Handler> handlers_;
};

/*
Example usage:

CommandDispatcher dispatcher;
dispatcher.registerCommand("MOVE", [&](const ParsedCommand& cmd) {
    supervisor.move(cmd.params);
});
dispatcher.registerCommand("NVSDIAG", [&](const ParsedCommand& cmd) {
    nvsManager.diagnostic(cmd.params);
});

// In your parser's dispatch callback:
if (!dispatcher.dispatch(cmd)) {
    // Handle unknown command
}
*/
