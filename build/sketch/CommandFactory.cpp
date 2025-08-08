#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\CommandFactory.cpp"
#include "CommandFactory.h"
#include <functional>

// Helper to wrap transition logic and response for set/action commands
// Usage: makeTransitionHandler([](cmd, supervisor) { ...build transitions... })
auto makeTransitionHandler = [](std::function<std::vector<StateTransition>(const ParsedCommand&, LegSupervisor&)> builder) {
    return [builder](const ParsedCommand& cmd, LegSupervisor& supervisor) {
        auto transitions = builder(cmd, supervisor);
        if (!transitions.empty()) {
            supervisor.queueTransitions(transitions);
            cmd.context.respond("+OK");
        }
    };
};

CommandHandler unsupportedHandler = [](const ParsedCommand& cmd, LegSupervisor&) {
    cmd.context.respond("+ERR:UNSUPPORTED_COMMAND_MODE");
};

// Default query handler: returns system state in format "+<command>? <systemstate>"
CommandHandler defaultQueryHandler = [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
    String response = "+" + cmd.command + "? " + String(static_cast<int>(supervisor.getCurrentState()));
    cmd.context.respond(response);
};

std::map<std::string, RegisteredCommand> CommandFactory::createCommands(LegSupervisor& supervisor) {
    std::map<std::string, RegisteredCommand> commands;

    // HOME
    commands["HOME"] = {
        {
            // Action handler
            // HOME: Move to neutral steering angle, 0 velocity, default slew time, then transition to Stopped
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // Define neutral as 135.0f, or use a config value if available
                float neutralSteering = 135.0f;
                float slewTime = supervisor.getSafeTiming(neutralSteering);
                return std::vector<StateTransition>{
                    // Fourth param 1.0f triggers raw movement for homing
                    {SystemState::ProcessMoveCmd, {neutralSteering, 0.0f, slewTime, 1.0f}},
                    {SystemState::Homed, {}}
                };
            }),
            unsupportedHandler, // Set
            defaultQueryHandler // Query
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Booting, SystemState::Stopped, SystemState::Parked}}
    };

    // MOVE
    commands["MOVE"] = {
        {
            unsupportedHandler, // Action
            // Set handler
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // AT+MOVE=steering_angle,velocity,slew_time
                // Params: [0]=steering_angle, [1]=velocity, [2]=slew_time
                // Validate parameter count
                if (cmd.params.size() < 3) {
                    cmd.context.respond("+ERR:INVALID_PARAMS");
                    return std::vector<StateTransition>{};
                }
                float steering_angle = cmd.params[0].toFloat();
                float velocity = cmd.params[1].toFloat();
                float slew_time = cmd.params[2].toFloat();
                // Build state transition sequence: ProcessMoveCmd -> Moving
                return std::vector<StateTransition>{
                    {SystemState::ProcessMoveCmd, {steering_angle, velocity, slew_time}},
                    {SystemState::Moving, {}}
                };
            }),
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
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float currentSteering = supervisor.getCurrentAngle();
                float slewTime = 1500.0f; // ms, fixed deceleration time for smooth stop
                return std::vector<StateTransition>{
                    {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, slewTime}},
                    {SystemState::Stopped, {}}
                };
            }),
            // Set handler: same as action, but slewTime is provided as a parameter
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float currentSteering = supervisor.getCurrentAngle();
                if (cmd.params.size() < 1) {
                    cmd.context.respond("+ERR:INVALID_PARAMS");
                    return std::vector<StateTransition>{};
                }
                float slewTime = cmd.params[0].toFloat();
                return std::vector<StateTransition>{
                    {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, slewTime}},
                    {SystemState::Stopped, {}}
                };
            }),
            defaultQueryHandler // Query
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Moving}}
    };

    // E_STOP
    commands["E_STOP"] = {
        {
            // E_STOP: Use ProcessMoveCmd to immediately set velocity to 0, then transition to EStop
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float currentSteering = supervisor.getCurrentAngle();
                float immediateSlew = 0.0f; // Immediate stop
                return std::vector<StateTransition>{
                    {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, immediateSlew}},
                    {SystemState::EStop, {}}
                };
            }),
            unsupportedHandler, // Set
            defaultQueryHandler // Query
        },
        CommandInfo{CommandPriority::PriorityCritical, {}}
    };

    // CAL (formerly SERVO_CAL and VERIFY_NVS)
    commands["CAL"] = {
        {
            // CAL action: no parameters required
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor&) {
                return std::vector<StateTransition>{
                    {SystemState::Calibrating, {}},
                    {SystemState::Stopped, {}}
                };
            }),
            /*
            // CAL set: transitions to Calibrating and passes parameters to setCal (placeholder)
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // Placeholder: pass all parameters to a hypothetical setCal function
                // supervisor.setCal(cmd.params); // Uncomment and refine when setCal is implemented
                return std::vector<StateTransition>{
                    {SystemState::Calibrating, SystemState::Stopped {}}
                };
            }),
            */
            unsupportedHandler, // Set (replace with above when ready)
            // CAL? query: respond with info only (no state change)
            [](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                // TODO: Replace with actual calibration info accessor
                cmd.context.respond("+CAL? info not implemented");
            }
        },
        CommandInfo{CommandPriority::PriorityHigh, {SystemState::Stopped, SystemState::Maintenance, SystemState::Parked, SystemState::Homed}}
    };

    // PARK
    commands["PARK"] = {
        {
            // PARK: Use ProcessMoveCmd to set steering angle for parking, velocity 0, then transition to Parked
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor& supervisor) {
                float parkSteering = supervisor.getParkSteeringAngle();
                float slewTime = supervisor.getSafeTiming(parkSteering);
                return std::vector<StateTransition>{
                    // Fourth param 1.0f triggers raw movement for parking
                    {SystemState::ProcessMoveCmd, {parkSteering, 0.0f, slewTime, 1.0f}},
                    {SystemState::Parked, {}}
                };
            }),
            unsupportedHandler, // Set
            defaultQueryHandler // Query
        },
        CommandInfo{CommandPriority::PriorityNormal, {SystemState::Stopped, SystemState::Homed}}
    };

    // NODE query command
    commands["NODE"] = {
        {
            unsupportedHandler, // Action
            unsupportedHandler, // Set
            // NODE query: respond with node number, no state change
            [](const ParsedCommand& cmd, LegSupervisor&) {
                cmd.context.respond("+NODE? " + String(cmd.nodeNumber));
            }
        },
        CommandInfo{CommandPriority::PriorityCritical, {}}
    };

    // OTA
    commands["OTA"] = {
        {
            // OTA command: no parameters required
            makeTransitionHandler([](const ParsedCommand& cmd, LegSupervisor&) {
                return std::vector<StateTransition>{
                    {SystemState::Updating, {}}
                };
            }),
            unsupportedHandler, // Set
            unsupportedHandler  // Query
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