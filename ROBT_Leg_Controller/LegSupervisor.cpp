#include "LegSupervisor.h"
#include <cmath>
#include <esp32-hal-ledc.h>

LegSupervisor::LegSupervisor(const ServoConfig& ServoCFG)
    : servo_(ServoCFG),
      hallSensor_(),
      servoCal_(servo_, ServoCFG){}

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