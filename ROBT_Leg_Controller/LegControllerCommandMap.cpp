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
    // TODO: Implement SMOOTH_STOP command logic
}

void handleEStopCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // TODO: Implement E_STOP command logic
}

void handleServoCalCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // TODO: Implement SERVO_CAL command logic
}

void handleVerifyNVSCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // TODO: Implement VERIFY_NVS command logic
}

void handleParkCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // TODO: Implement PARK command logic
}

void handleNodeCommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // TODO: Implement NODE command logic
}

void handleOTACommand(const ParsedCommand& cmd, LegSupervisor& supervisor) {
    // TODO: Implement OTA command logic
}