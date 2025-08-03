#ifndef LEG_CONTROLLER_COMMAND_MAP_H
#define LEG_CONTROLLER_COMMAND_MAP_H

#include "CommandDispatcher.h"
#include "LegSupervisor.h"
#include "NVSManager.h"
// Add other module headers as needed

// Centralized registration of all AT commands
inline void registerAllCommands(CommandDispatcher& dispatcher, LegSupervisor& supervisor /*, ... */) {
    dispatcher.registerCommand("MOVE", [&](const ParsedCommand& cmd) {
        supervisor.move(cmd.params);
    });
    dispatcher.registerCommand("SMOOTH_STOP", [&](const ParsedCommand& cmd) {
        supervisor.smoothStop(cmd.params);
    });
    dispatcher.registerCommand("E_STOP", [&](const ParsedCommand& cmd) {
        supervisor.emergencyStop(cmd.params);
    });
    dispatcher.registerCommand("SERVO_CAL", [&](const ParsedCommand& cmd) {
        supervisor.calibrateServo(cmd.params);
    });
    dispatcher.registerCommand("VERIFY_NVS", [&](const ParsedCommand& cmd) {
        supervisor.verifyNVS(cmd.params);
    });
    dispatcher.registerCommand("PARK", [&](const ParsedCommand& cmd) {
        supervisor.park(cmd.params);
    });
    // Example diagnostic command
    dispatcher.registerCommand("NVSDIAG", [&](const ParsedCommand& cmd) {
        NVSManager::diagnostic(cmd.params);
    });
    // Add more commands as needed
}

#endif // LEG_CONTROLLER_COMMAND_MAP_H