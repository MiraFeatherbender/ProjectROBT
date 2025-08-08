#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\ServoController.cpp"
#include "ServoController.h"
#include <cmath>
#include <esp32-hal-ledc.h>

ServoController::ServoController(const ServoConfig& config)
    : cfg_(config) {}

void ServoController::begin() {
    //setAngle(135.0f);
}

// Public API — safe for general motion control
void ServoController::setAngle(float angle_deg, uint32_t fade_time_ms) {
    float clamped = std::min(std::max(angle_deg, cfg_.motion_window_min), cfg_.motion_window_max);
    setAngleRaw(clamped, fade_time_ms);
}

// Internal / calibration use — bypasses logic window
void ServoController::setAngleRaw(float angle_deg, uint32_t fade_time_ms) {
    if (fade_time_ms == 0) {
        fade_time_ms = calculateFadeTimeMs(angle_deg, current_angle_);
    }
    int target_duty = angleToDuty(angle_deg);
    int current_duty = ledcRead(cfg_.ledc.pin);

    ledcFade(cfg_.ledc.pin, current_duty, target_duty, fade_time_ms);
    current_angle_ = angle_deg;
}

// Public utility for fade time calculation based on angular velocity
uint32_t ServoController::calculateFadeTimeMs(float target_angle, float current_angle) const {
    float delta_deg = std::abs(target_angle - current_angle);
    float seconds = (cfg_.max_deg_per_sec > 0.0f)
                      ? (delta_deg / cfg_.max_deg_per_sec)
                      : 0.0f;
    return static_cast<uint32_t>(seconds * 1000.0f);
}

void ServoController::initializeAngle(float angle){
    int target_duty = angleToDuty(angle);
    ledcFade(cfg_.ledc.pin, target_duty, target_duty, 1); // Initialize LEDC PWM to known value for setAngleRaw fade
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

uint32_t ServoController::getPulseUS() const {
    int raw_duty = ledcRead(cfg_.ledc.pin);
    uint32_t period_us = static_cast<uint32_t>(1e6 / cfg_.ledc.frequency);
    int max_duty = (1 << cfg_.ledc.resolution_bits) - 1;

    return static_cast<uint32_t>((raw_duty / static_cast<float>(max_duty)) * period_us);
}

void ServoController::setBootAngle(float angle) {
    current_angle_ = angle;
}