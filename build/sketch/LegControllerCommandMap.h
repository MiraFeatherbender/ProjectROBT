#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\LegControllerCommandMap.h"
#ifndef LEG_CONTROLLER_COMMAND_MAP_H
#define LEG_CONTROLLER_COMMAND_MAP_H

#include "CommandDispatcher.h"
#include "LegSupervisor.h"
#include "NVSManager.h"
#include "CommandInfo.h"

// Handler prototypes
void handleMoveCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleSmoothStopCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleEStopCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleServoCalCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleVerifyNVSCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleParkCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleNodeCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleOTACommand(const ParsedCommand& cmd, LegSupervisor& supervisor);
void handleHomeCommand(const ParsedCommand& cmd, LegSupervisor& supervisor);

inline void registerAllCommands(CommandDispatcher& dispatcher, LegSupervisor& supervisor) {
    dispatcher.registerCommand(
        "MOVE",
        [&](const ParsedCommand& cmd) { handleMoveCommand(cmd, supervisor); },
        // Allowed only from Stopped or Moving (for smooth chaining)
        CommandInfo{CommandPriority::PriorityNormal, {SystemState::Stopped, SystemState::Moving, SystemState::Homed}}
    );
    dispatcher.registerCommand(
        "SMOOTH_STOP",
        [&](const ParsedCommand& cmd) { handleSmoothStopCommand(cmd, supervisor); },
        // Only allowed during Moving
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Moving}}
    );
    dispatcher.registerCommand(
        "E_STOP",
        [&](const ParsedCommand& cmd) { handleEStopCommand(cmd, supervisor); },
        // Allowed from any state except Booting (but Booting included for safety)
        CommandInfo{CommandPriority::PriorityCritical, {
            SystemState::Booting, SystemState::Parked, SystemState::Homed, SystemState::Stopped, SystemState::ProcessMoveCmd,
            SystemState::Moving, SystemState::EStop, SystemState::Maintenance, SystemState::Updating
        }}
    );
    dispatcher.registerCommand(
        "SERVO_CAL",
        [&](const ParsedCommand& cmd) { handleServoCalCommand(cmd, supervisor); },
        // Allowed from Stopped or Maintenance
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Stopped, SystemState::Maintenance, 
        SystemState::Parked, SystemState::Homed}}
    );
    dispatcher.registerCommand(
        "VERIFY_NVS",
        [&](const ParsedCommand& cmd) { handleVerifyNVSCommand(cmd, supervisor); },
        // Allowed from Stopped, Maintenance, or Parked
        CommandInfo{CommandPriority::PriorityNormal, {SystemState::Stopped, SystemState::Maintenance, 
        SystemState::Homed, SystemState::Parked}}
    );
    dispatcher.registerCommand(
        "PARK",
        [&](const ParsedCommand& cmd) { handleParkCommand(cmd, supervisor); },
        // Only allowed from Stopped
        CommandInfo{CommandPriority::PriorityNormal, {SystemState::Stopped, SystemState::Homed}}
    );
    dispatcher.registerCommand(
        "NODE",
        [&](const ParsedCommand& cmd) { handleNodeCommand(cmd, supervisor); },
        // Allowed in all states except Booting
        CommandInfo{CommandPriority::PriorityLow, {
            SystemState::Parked, SystemState::Homed, SystemState::Stopped, SystemState::Moving, 
            SystemState::EStop
        }}
    );
    dispatcher.registerCommand(
        "OTA",
        [&](const ParsedCommand& cmd) { handleOTACommand(cmd, supervisor); },
        // Allowed only from Maintenance
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Maintenance}}
    );
    dispatcher.registerCommand(
        "HOME",
        [&](const ParsedCommand& cmd) { handleHomeCommand(cmd, supervisor); },
        // Allowed from Booting, Stopped, and Moving
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Booting, SystemState::Stopped, SystemState::Parked}}
    );
    // Add more commands as needed
}

#endif // LEG_CONTROLLER_COMMAND_MAP_H