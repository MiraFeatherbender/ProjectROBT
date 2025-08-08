#include "CommandFactory.h"

CommandHandler unsupportedHandler = [](const ParsedCommand& cmd, LegSupervisor&) {
    cmd.context.respond("+ERR:UNSUPPORTED_COMMAND_MODE");
};

std::map<std::string, RegisteredCommand> CommandFactory::createCommands(LegSupervisor& supervisor) {
    std::map<std::string, RegisteredCommand> commands;

    // HOME
    commands["HOME"] = {
        {
            // Action handler
            // HOME: Move to neutral steering angle, 0 velocity, default slew time, then transition to Stopped
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // Define neutral as 135.0f, or use a config value if available
                float neutralSteering = 135.0f;
                float slewTime = supervisor.getSafeTiming(neutralSteering);
                std::vector<StateTransition> transitions = {
                    // Fourth param 1.0f triggers raw movement for homing
                    {SystemState::ProcessMoveCmd, {neutralSteering, 0.0f, slewTime, 1.0f}},
                    {SystemState::Homed, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:HOME queued");
            },
            // Set handler
            unsupportedHandler,
            // Query handler (placeholder)
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // Returns homed status (true/false)
               // bool isHomed = supervisor.isHomed(); // Assuming this method exists
                cmd.context.respond("+HOME? homed=");// + String(isHomed));
            }
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Booting, SystemState::Stopped, SystemState::Parked}}
    };

    // MOVE
    commands["MOVE"] = {
        {
            // Action handler: unsupported
            unsupportedHandler,
            // Set handler
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // AT+MOVE=steering_angle,velocity,slew_time
                // Params: [0]=steering_angle, [1]=velocity, [2]=slew_time
                // Validate parameter count
                if (cmd.params.size() < 3) {
                    cmd.context.respond("+ERR:INVALID_PARAMS");
                    return;
                }
                float steering_angle = cmd.params[0].toFloat();
                float velocity = cmd.params[1].toFloat();
                float slew_time = cmd.params[2].toFloat();
                // Build state transition sequence: ProcessMoveCmd -> Moving
                std::vector<StateTransition> transitions = {
                    {SystemState::ProcessMoveCmd, {steering_angle, velocity, slew_time}},
                    {SystemState::Moving, {}}
                };
                // Queue transitions in LegSupervisor
                supervisor.queueTransitions(transitions);
                // Respond with ACK
                cmd.context.respond("+ACK");
            },
            // Query handler (placeholder)
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // Returns current angle and velocity
                float currentAngle = supervisor.getCurrentAngle();
                //float currentVelocity = supervisor.getCurrentVelocity(); // Assuming this method exists
                cmd.context.respond("+MOVE? angle=" + String(currentAngle));// + ", velocity=" + String(currentVelocity));
            }
        },
        CommandInfo{CommandPriority::PriorityNormal, {SystemState::Stopped, SystemState::Moving, SystemState::Homed}}
    };

    // SMOOTH_STOP
    commands["SMOOTH_STOP"] = {
        {
            // SMOOTH_STOP: Use ProcessMoveCmd to ramp velocity to 0, keep steering steady, then transition to Stopped
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float currentSteering = supervisor.getCurrentAngle();
                float slewTime = 1500.0f; // ms, fixed deceleration time for smooth stop
                std::vector<StateTransition> transitions = {
                    {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, slewTime}},
                    {SystemState::Stopped, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:SMOOTH_STOP queued");
            },
            unsupportedHandler,
            unsupportedHandler
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Moving}}
    };

    // E_STOP
    commands["E_STOP"] = {
        {
            // E_STOP: Use ProcessMoveCmd to immediately set velocity to 0, then transition to EStop
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float currentSteering = supervisor.getCurrentAngle();
                float immediateSlew = 0.0f; // Immediate stop
                std::vector<StateTransition> transitions = {
                    {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, immediateSlew}},
                    {SystemState::EStop, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:E_STOP queued");
            },
            unsupportedHandler,
            unsupportedHandler
        },
        CommandInfo{CommandPriority::PriorityCritical, {
            SystemState::Booting, SystemState::Parked, SystemState::Homed, SystemState::Stopped, SystemState::ProcessMoveCmd,
            SystemState::Moving, SystemState::EStop, SystemState::Maintenance, SystemState::Updating
        }}
    };

    // CAL (formerly SERVO_CAL and VERIFY_NVS)
    commands["CAL"] = {
        {
            // CAL action: no parameters required
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                std::vector<StateTransition> transitions = {
                    {SystemState::Calibrating, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:CAL queued");
            },
            unsupportedHandler,
            // CAL? (formerly VERIFY_NVS): no parameters required
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                std::vector<StateTransition> transitions = {
                    {SystemState::Maintenance, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:CAL? queued");
            }
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Stopped, SystemState::Maintenance, SystemState::Parked, SystemState::Homed}}
    };

    // CAL query: formerly VERIFY_NVS
    commands["CAL"].handlers.query = [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
        // CAL? (formerly VERIFY_NVS): no parameters required
        std::vector<StateTransition> transitions = {
            {SystemState::Maintenance, {}}
        };
        supervisor.queueTransitions(transitions);
        cmd.context.respond("+ACK:CAL? queued");
    };

    // PARK
    commands["PARK"] = {
        {
            // PARK: Use ProcessMoveCmd to set steering angle for parking, velocity 0, then transition to Parked
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float parkSteering = supervisor.getParkSteeringAngle();
                float slewTime = supervisor.getSafeTiming(parkSteering);
                std::vector<StateTransition> transitions = {
                    // Fourth param 1.0f triggers raw movement for parking
                    {SystemState::ProcessMoveCmd, {parkSteering, 0.0f, slewTime, 1.0f}},
                    {SystemState::Parked, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:PARK queued");
            },
            unsupportedHandler,
            unsupportedHandler
        },
        CommandInfo{CommandPriority::PriorityNormal, {SystemState::Stopped, SystemState::Homed}}
    };

    // NODE query command
    commands["NODE"] = {
        {
            unsupportedHandler,
            unsupportedHandler,
            // NODE query: no parameters required
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                std::vector<StateTransition> transitions = {
                    {SystemState::Stopped, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:NODE? queued");
            }
        },
        CommandInfo{CommandPriority::PriorityLow, {SystemState::Parked, SystemState::Homed, SystemState::Stopped, SystemState::Moving, SystemState::EStop}}
    };

    // OTA
    commands["OTA"] = {
        {
            // OTA command: no parameters required
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                std::vector<StateTransition> transitions = {
                    {SystemState::Updating, {}}
                };
                supervisor.queueTransitions(transitions);
                cmd.context.respond("+ACK:OTA queued");
            },
            unsupportedHandler,
            unsupportedHandler
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Maintenance}}
    };

    return commands;
}

// --- Command Registration Utility ---
void CommandFactory::registerAll(CommandDispatcher& dispatcher, LegSupervisor& supervisor) {
    auto commandMap = createCommands(supervisor);
    for (const auto& [cmdName, regCmd] : commandMap) {
        dispatcher.registerCommand(
            cmdName,
            [handlerSet = regCmd.handlers, &supervisor](const ParsedCommand& cmd) {
                switch (cmd.type) {
                    case CommandType::Action: handlerSet.action(cmd, supervisor); break;
                    case CommandType::Set:    handlerSet.set(cmd, supervisor);    break;
                    case CommandType::Query:  handlerSet.query(cmd, supervisor);  break;
                }
            },
            regCmd.info
        );
    }
}