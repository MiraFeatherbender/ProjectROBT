#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include "DriveConfig.h"

class ServoController {
public:
    explicit ServoController(const ServoConfig& config);

    void begin();                       // Optional state init, but no hardware setup
    void setAngle(float angle_deg, uint32_t fade_time_ms = 0);     // Moves to target angle via PWM fade with clamping; fade_time_ms=0 uses calculated
    void setAngleRaw(float angle_deg, uint32_t fade_time_ms = 0);  // Moves to target angle via PWM fade without clamping; fade_time_ms=0 uses calculated
    void initializeAngle(float angle);  // Stabilizes initial servo angle PWM
    float getAngle() const;             // Returns last commanded angle
    uint32_t getPulseUS() const;        // Returns active pulse width in uS
    void setBootAngle(float angle);     // Sets internal angle without PWM fade

    // Public utility for fade time calculation based on angular velocity
    uint32_t calculateFadeTimeMs(float target_angle, float current_angle) const;

    const LEDCConfig& getLEDCConfig() const { // Returns config needed to setup LEDC hardware
        return cfg_.ledc;}

private:
    ServoConfig cfg_;
    float current_angle_;

    int angleToDuty(float angle) const; // Converts angle to PWM duty cycle
};

#endif // SERVO_CONTROLLER_H