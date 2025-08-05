#ifndef LEG_CONTROLLER_COMMAND_MAP_H
#define LEG_CONTROLLER_COMMAND_MAP_H

#include "CommandDispatcher.h"
#include "LegSupervisor.h"
#include "NVSManager.h"
#include "CommandInfo.h"

inline void registerAllCommands(CommandDispatcher& dispatcher, LegSupervisor& supervisor) {
    dispatcher.registerCommand(
        "MOVE",
        [&](const ParsedCommand& cmd) { supervisor.handleParsedCommand(cmd); },
        CommandInfo{CommandPriority::NORMAL, {SystemState::Stopped, SystemState::Moving}}
    );
    dispatcher.registerCommand(
        "SMOOTH_STOP",
        [&](const ParsedCommand& cmd) { supervisor.handleParsedCommand(cmd); },
        CommandInfo{CommandPriority::HIGH, {SystemState::Moving}}
    );
    dispatcher.registerCommand(
        "E_STOP",
        [&](const ParsedCommand& cmd) { supervisor.handleParsedCommand(cmd); },
        CommandInfo{CommandPriority::CRITICAL, {SystemState::Booting, SystemState::Parked, SystemState::Stopped, SystemState::Moving, SystemState::EStop, SystemState::Maintenance, SystemState::Updating}}
    );
    dispatcher.registerCommand(
        "SERVO_CAL",
        [&](const ParsedCommand& cmd) { supervisor.handleParsedCommand(cmd); },
        CommandInfo{CommandPriority::HIGH, {SystemState::Stopped, SystemState::Maintenance}}
    );
    dispatcher.registerCommand(
        "VERIFY_NVS",
        [&](const ParsedCommand& cmd) { supervisor.handleParsedCommand(cmd); },
        CommandInfo{CommandPriority::NORMAL, {SystemState::Stopped, SystemState::Maintenance, SystemState::Parked}}
    );
    dispatcher.registerCommand(
        "PARK",
        [&](const ParsedCommand& cmd) { supervisor.handleParsedCommand(cmd); },
        CommandInfo{CommandPriority::NORMAL, {SystemState::Stopped}}
    );
    dispatcher.registerCommand(
        "NODE",
        [](const ParsedCommand& cmd){
            cmd.context.respond("+OK:Node number is " + String(cmd.nodeNumber));
        },
        CommandInfo{CommandPriority::LOW, {SystemState::Booting, SystemState::Parked, SystemState::Stopped, SystemState::Moving, SystemState::EStop, SystemState::Maintenance, SystemState::Updating}}
    );
    // Add more commands as needed
}

#endif // LEG_CONTROLLER_COMMAND_MAP_H