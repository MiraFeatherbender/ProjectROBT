#include "LegSupervisor.h"
#include <cmath>
#include <esp32-hal-ledc.h>

LegSupervisor::LegSupervisor(const ServoConfig& ServoCFG)
    : servo_(ServoCFG) {}

bool LegSupervisor::begin() {
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