#include "ServoController.h"
#include <cmath>
#include <esp32-hal-ledc.h>

ServoController::ServoController(const ServoConfig& config)
    : cfg_(config) {}

void ServoController::begin() {
    setAngle(225.0f);
}

// Public API — safe for general motion control
void ServoController::setAngle(float angle_deg) {
    float clamped = std::min(std::max(angle_deg, cfg_.motion_window_min), cfg_.motion_window_max);
    setAngleRaw(clamped);
}

// Internal / calibration use — bypasses logic window
void ServoController::setAngleRaw(float angle_deg) {
    float delta_deg = std::abs(angle_deg - current_angle_);

    float seconds = (cfg_.max_deg_per_sec > 0.0f)
                      ? (delta_deg / cfg_.max_deg_per_sec)
                      : 0.0f;

    uint32_t fade_time_ms = static_cast<uint32_t>(seconds * 1000.0f);
    int target_duty = angleToDuty(angle_deg);
    int current_duty = ledcRead(cfg_.ledc.pin);

    ledcFade(cfg_.ledc.pin, current_duty, target_duty, fade_time_ms);
    current_angle_ = angle_deg;
}

void ServoController::initializeAngle(float angle){
    int target_duty = angleToDuty(angle);
    ledcFade(cfg_.ledc.pin, target_duty, target_duty, 1); // Initialize PWM for proper fade
}

int ServoController::angleToDuty(float angle) const {
    // Map clamped angle into physical travel range
    float normalized = (angle - cfg_.angle_min_deg) /
                       (cfg_.angle_max_deg - cfg_.angle_min_deg);

    // Scale to pulse width range
    float pulse_us = normalized * (cfg_.pulse_max_us - cfg_.pulse_min_us) +
                     cfg_.pulse_min_us;

    float period_us = 1e6f / cfg_.ledc.frequency;
    int max_duty = (1 << cfg_.ledc.resolution_bits) - 1;

    return static_cast<int>((pulse_us / period_us) * max_duty);
}

float ServoController::getAngle() const {
    return current_angle_;
}

void ServoController::setBootAngle(float angle) {
    current_angle_ = angle;
}

float ServoController::getAngleMin() const {
    return cfg_.angle_min_deg;
}

float ServoController::getAngleMax() const {
    return cfg_.angle_max_deg;
}