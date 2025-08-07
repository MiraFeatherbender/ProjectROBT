// Required includes for type definitions
#include "LegControllerCommandMap.h"
#include "ParsedCommand.h"
#include "LegSupervisor.h"
#include "CommandInfo.h"
#include <vector>

void handleHomeCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // HOME: Move to neutral steering angle, 0 velocity, default slew time, then transition to Stopped
    float neutralSteering = 135.0f; // Define neutral as 135.0f, or use a config value if available
    float slewTime = supervisor.getSafeTiming(neutralSteering);
    std::vector<StateTransition> transitions = {
        // Fourth param 1.0f triggers raw movement for homing
        {SystemState::ProcessMoveCmd, {neutralSteering, 0.0f, slewTime, 1.0f}},
        {SystemState::Homed, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:HOME queued");
}
#include "LegControllerCommandMap.h"

void handleMoveCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // Example: AT+MOVE=steering_angle,velocity,slew_time
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
}

void handleSmoothStopCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // SMOOTH_STOP: Use ProcessMoveCmd to ramp velocity to 0, keep steering steady, then transition to Stopped
    float currentSteering = supervisor.getCurrentAngle();
    float slewTime = 1500.0f; // ms, fixed deceleration time for smooth stop
    std::vector<StateTransition> transitions = {
        {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, slewTime}},
        {SystemState::Stopped, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:SMOOTH_STOP queued");
}

void handleEStopCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // E_STOP: Use ProcessMoveCmd to immediately set velocity to 0, then transition to EStop
    float currentSteering = supervisor.getCurrentAngle();
    float immediateSlew = 0.0f; // Immediate stop
    std::vector<StateTransition> transitions = {
        {SystemState::ProcessMoveCmd, {currentSteering, 0.0f, immediateSlew}},
        {SystemState::EStop, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:E_STOP queued");
}

void handleServoCalCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // SERVO_CAL command: no parameters required
    std::vector<StateTransition> transitions = {
        {SystemState::Calibrating, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:SERVO_CAL queued");
}

void handleVerifyNVSCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // VERIFY_NVS command: no parameters required
    std::vector<StateTransition> transitions = {
        {SystemState::Maintenance, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:VERIFY_NVS queued");
}

void handleParkCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // PARK: Use ProcessMoveCmd to set steering angle for parking, velocity 0, then transition to Parked
    float parkSteering = supervisor.getParkSteeringAngle();
    float slewTime = supervisor.getSafeTiming(parkSteering);
    std::vector<StateTransition> transitions = {
        // Fourth param 1.0f triggers raw movement for parking
        {SystemState::ProcessMoveCmd, {parkSteering, 0.0f, slewTime, 1.0f}},
        {SystemState::Parked, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:PARK queued");
}

void handleNodeCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // NODE command: no parameters required
    std::vector<StateTransition> transitions = {
        {SystemState::Stopped, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:NODE queued");
}

void handleOTACommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // OTA command: no parameters required
    std::vector<StateTransition> transitions = {
        {SystemState::Updating, {}}
    };
    supervisor.queueTransitions(transitions);
    cmd.context.respond("+ACK:OTA queued");
}