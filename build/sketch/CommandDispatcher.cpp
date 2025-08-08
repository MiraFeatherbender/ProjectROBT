#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\CommandDispatcher.cpp"
#include "CommandDispatcher.h"

void CommandDispatcher::registerCommand(const std::string& cmd, Handler handler, const CommandInfo& info) {
    commands_[cmd] = RegisteredCommand{handler, info};
}

void CommandDispatcher::clear() {
    commands_.clear();
}

bool CommandDispatcher::isAllowed(const CommandInfo& info, SystemState currentState, CommandPriority currentPriority) const {
    switch (info.priority) {
        case CommandPriority::PriorityCritical:
            return true;
        default:
            for (auto allowed : info.allowedStates) {
                if (allowed == currentState) {
                    return info.priority >= currentPriority;
                }
            }
            return false;
    }
}

bool CommandDispatcher::dispatch(const ParsedCommand& cmd, LegSupervisor& supervisor) const {
    const auto& reg = commands_.at(std::string(cmd.command.c_str()));
    SystemState currentState = supervisor.getCurrentState();
    CommandPriority currentPriority = supervisor.getCurrentPriority();

    switch (cmd.type) {
        case CommandType::Query:
            reg.handler(cmd);
            return true;
        default:
            if (!isAllowed(reg.info, currentState, currentPriority)) {
                return false;
            }
            if (reg.info.priority >= currentPriority) {
                supervisor.clearTransitionQueue();
            }
            reg.handler(cmd);
            return true;
    }
}

const CommandInfo* CommandDispatcher::getCommandInfo(const std::string& cmd) const {
    auto it = commands_.find(cmd);
    if (it != commands_.end()) {
        return &it->second.info;
    }
    return nullptr;
}

