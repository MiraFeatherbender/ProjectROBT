#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include "DriveConfig.h"

class ServoController {
public:
    explicit ServoController(const ServoConfig& config);

    void begin();                       // Optional state init, but no hardware setup
    void setAngle(float angle_deg);     // Moves to target angle via PWM fade with clamping
    void setAngleRaw(float angle_deg);  // Moves to target angle via PWM fade without clamping
    void initializeAngle(float angle);  // Stabilizes initial servo angle PWM
    float getAngle() const;             // Returns last commanded angle
    uint32_t getPulseUS() const;        // Returns active pulse width in uS
    void setBootAngle(float angle);     // Sets internal angle without PWM fade

    const LEDCConfig& getLEDCConfig() const { // Returns config needed to setup LEDC hardware
        return cfg_.ledc;}

private:
    ServoConfig cfg_;
    float current_angle_;

    int angleToDuty(float angle) const; // Converts angle to PWM duty cycle
};

#endif // SERVO_CONTROLLER_H