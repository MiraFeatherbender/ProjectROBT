
#include "LegSupervisor.h"
#include <cmath>
#include <esp32-hal-ledc.h>

// Clear the transition queue and reset ProcessMoveCmd timer/lockout
void LegSupervisor::clearTransitionQueue() {
    transitionQueue_.clear();
    moveCmdActive_ = false;
    moveCmdStartTime_ = 0;
    moveCmdSlewTime_ = 0.0f;
}

LegSupervisor::LegSupervisor(const ServoConfig& ServoCFG)
    : servo_(ServoCFG),
      hallSensor_(),
      servoCal_(servo_, ServoCFG),
      defaultSlewTime_(1.0f),
      parkSteeringAngle_(0.0f) {}

bool LegSupervisor::begin() {
    servo_.begin();
    if (!attachLEDC(servo_.getLEDCConfig())) return false;
    return true;
}

void LegSupervisor::captureInitialAngle(uint16_t raw_mv) {
    float angle = -(raw_mv / 3.0f) + 302.0f;
    // Clamp angle to configured range
    angle = std::min(std::max(angle, 0.0f), 270.0f);

    servo_.setBootAngle(angle);
    servo_.initializeAngle(angle);
}

float LegSupervisor::getCurrentAngle() const {
    return servo_.getAngle();  // Or directly return if public
}

bool LegSupervisor::attachLEDC(const LEDCConfig& cfg) {
    return ledcAttach(cfg.pin, cfg.frequency, cfg.resolution_bits);
}

void LegSupervisor::setSteeringAngle(float angle) {
    servo_.setAngle(angle);
}

void LegSupervisor::setRawSteeringAngle(float angle){
    servo_.setAngleRaw(angle);
}

void LegSupervisor::handleParsedCommand(const ParsedCommand& cmd) {
    String response = "+ACK: node=" + String(cmd.nodeNumber) + ", cmd='" + cmd.command + "'";
    if (!cmd.params.empty()) {
        response += ", params=";
        for (size_t i = 0; i < cmd.params.size(); ++i) {
            response += cmd.params[i];
            if (i < cmd.params.size() - 1) response += ",";
        }
    }
    if (cmd.isOTA) response += ", OTA=1";
    cmd.context.respond(response); // Send response back to source
}

void LegSupervisor::initADC(ADCConfig& cfg, void (*callback)()) {
    analogContinuousSetWidth(cfg.width_bits);
    analogContinuousSetAtten(cfg.attenuation);
    analogContinuous(cfg.pins, cfg.pin_count, cfg.conversions_per_pin, cfg.sampling_frequency, callback);
    analogContinuousStart();
}

bool LegSupervisor::saveSweepSummary(){
    SweepSummary summary = servoCal_.getSweepSummary();
    return NVSManager::storeSweepSummary(summary);
}

void LegSupervisor::queueTransitions(const std::vector<StateTransition>& transitions) {
    for (const auto& t : transitions) {
        transitionQueue_.push_back(t);
    }
}

void LegSupervisor::update() {
    if (!transitionQueue_.empty()) {
        auto& transition = transitionQueue_.front();
        switch (transition.nextState) {
            case SystemState::Booting:
                currentState_ = SystemState::Booting;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::Parked:
                currentState_ = SystemState::Parked;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::Homed:
                currentState_ = SystemState::Homed;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::Stopped:
                currentState_ = SystemState::Stopped;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::ProcessMoveCmd:
                // Timer-based non-blocking slew enforcement
                if (!moveCmdActive_) {
                    if (transition.params.size() >= 3) {
                        float steering = transition.params[0];
                        float velocity = transition.params[1];
                        float slew = transition.params[2];
                        setSteeringAngle(steering); // TODO: add slew support
                        // TODO: setDriveVelocity(velocity, slew); // Placeholder for future stepper logic
                        moveCmdActive_ = true;
                        moveCmdStartTime_ = millis();
                        moveCmdSlewTime_ = slew;
                    }
                }
                // Only advance if slew time has elapsed
                if (moveCmdActive_ && (millis() - moveCmdStartTime_ >= (unsigned long)(moveCmdSlewTime_ * 1000.0f))) {
                    moveCmdActive_ = false;
                    moveCmdStartTime_ = 0;
                    moveCmdSlewTime_ = 0.0f;
                    // Advance to next state in queue (if any)
                    transitionQueue_.erase(transitionQueue_.begin());
                }
                // Otherwise, stay in ProcessMoveCmd until timer expires
                break;
            case SystemState::Moving:
                currentState_ = SystemState::Moving;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::EStop:
                currentState_ = SystemState::EStop;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::Maintenance:
                currentState_ = SystemState::Maintenance;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::Calibrating:
                currentState_ = SystemState::Calibrating;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            case SystemState::Updating:
                currentState_ = SystemState::Updating;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
            default:
                currentState_ = transition.nextState;
                transitionQueue_.erase(transitionQueue_.begin());
                break;
        }
    }
}