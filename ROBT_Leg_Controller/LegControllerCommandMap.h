#ifndef LEG_CONTROLLER_COMMAND_MAP_H
#define LEG_CONTROLLER_COMMAND_MAP_H

#include "CommandDispatcher.h"
#include "LegSupervisor.h"
#include "NVSManager.h"
// Add other module headers as needed

// Centralized registration of all AT commands
inline void registerAllCommands(CommandDispatcher& dispatcher, LegSupervisor& supervisor /*, ... */) {
    dispatcher.registerCommand("AT+MOVE=", [&](const ParsedCommand& cmd) {
        supervisor.handleParsedCommand(cmd);
    });
    dispatcher.registerCommand("AT+SMOOTH_STOP=", [&](const ParsedCommand& cmd) {
        supervisor.handleParsedCommand(cmd);
    });
    dispatcher.registerCommand("AT+E_STOP=", [&](const ParsedCommand& cmd) {
        supervisor.handleParsedCommand(cmd);
    });
    dispatcher.registerCommand("AT+SERVO_CAL=", [&](const ParsedCommand& cmd) {
        supervisor.handleParsedCommand(cmd);
    });
    dispatcher.registerCommand("AT+VERIFY_NVS=", [&](const ParsedCommand& cmd) {
        supervisor.handleParsedCommand(cmd);
    });
    dispatcher.registerCommand("AT+PARK=", [&](const ParsedCommand& cmd) {
        supervisor.handleParsedCommand(cmd);
    });
    // Example diagnostic command
    // dispatcher.registerCommand("AT+NVSDIAG=", [&](const ParsedCommand& cmd) {
    //     NVSManager::diagnostic(cmd.params);
    // });
    // Add more commands as needed
}

#endif // LEG_CONTROLLER_COMMAND_MAP_H