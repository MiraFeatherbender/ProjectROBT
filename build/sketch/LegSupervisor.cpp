#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\LegSupervisor.cpp"
#include "LegSupervisor.h"
#include <cmath>
#include <esp32-hal-ledc.h>

// Initialization & Setup
LegSupervisor::LegSupervisor(const ServoConfig& ServoCFG)
    : servo_(ServoCFG),
      hallSensor_(),
      servoCal_(servo_, ServoCFG),
      parkSteeringAngle_(135.0f) {}

bool LegSupervisor::begin() {
    if (!attachLEDC(servo_.getLEDCConfig())) return false;
    return true;
}

void LegSupervisor::initADC(ADCConfig& cfg, void (*callback)()) {
    analogContinuousSetWidth(cfg.width_bits);
    analogContinuousSetAtten(cfg.attenuation);
    analogContinuous(cfg.pins, cfg.pin_count, cfg.conversions_per_pin, cfg.sampling_frequency, callback);
    analogContinuousStart();
}

void LegSupervisor::captureInitialAngle(uint16_t raw_mv) {
    float angle = -(raw_mv / 3.0f) + 302.0f;
    // Clamp angle to configured range
    angle = std::min(std::max(angle, 0.0f), 270.0f);

    servo_.setBootAngle(angle);
    servo_.initializeAngle(angle);
}

bool LegSupervisor::attachLEDC(const LEDCConfig& cfg) {
    return ledcAttach(cfg.pin, cfg.frequency, cfg.resolution_bits);
}

// State Machine & Transitions
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
                        bool useRaw = (transition.params.size() >= 4) ? (transition.params[3] != 0.0f) : false;
                        if (useRaw) {
                            setRawSteeringAngle(steering);
                        } else {
                            setSteeringAngle(steering);
                        }
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
                // Minimal non-blocking Hall LED blink
                {
                    unsigned long now = millis();
                    if (now - hallLedLastToggle_ >= 250) { // 250ms interval
                        hallLedState_ = !hallLedState_;
                        digitalWrite(HALL_LED, hallLedState_ ? HIGH : LOW);
                        hallLedLastToggle_ = now;
                    }
                }
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

void LegSupervisor::queueTransitions(const std::vector<StateTransition>& transitions) {
    for (const auto& t : transitions) {
        transitionQueue_.push_back(t);
    }
}

void LegSupervisor::clearTransitionQueue() {
    transitionQueue_.clear();
    moveCmdActive_ = false;
    moveCmdStartTime_ = 0;
    moveCmdSlewTime_ = 0.0f;
}

// Servo Control
void LegSupervisor::setSteeringAngle(float angle) {
    servo_.setAngle(angle);
}

void LegSupervisor::setRawSteeringAngle(float angle){
    servo_.setAngleRaw(angle);
}

float LegSupervisor::getCurrentAngle() const {
    return servo_.getAngle();  // Or directly return if public
}

uint32_t LegSupervisor::getSafeTiming(float prescribedAngle) const {
    return servo_.calculateFadeTimeMs(prescribedAngle, getCurrentAngle());
}

// Command Handling
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

// Persistence
bool LegSupervisor::saveSweepSummary(){
    SweepSummary summary = servoCal_.getSweepSummary();
    return NVSManager::storeSweepSummary(summary);
}