#pragma once
#include <map>
#include <string>
#include "ParsedCommand.h"
#include "LegSupervisor.h"
#include "CommandInfo.h"
#include "CommandDispatcher.h"

using CommandHandler = std::function<void(const ParsedCommand&, LegSupervisor&)>;

struct CommandHandlerSet {
    CommandHandler action;
    CommandHandler set;
    CommandHandler query;
};

struct RegisteredCommand {
    CommandHandlerSet handlers;
    CommandInfo info;
};

class CommandFactory {
public:
    static std::map<std::string, RegisteredCommand> createCommands(LegSupervisor& supervisor);
    static void registerAll(CommandDispatcher& dispatcher, LegSupervisor& supervisor);
};
