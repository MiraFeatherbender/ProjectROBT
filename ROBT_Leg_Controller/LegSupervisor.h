#ifndef LEG_SUPERVISOR_H
#define LEG_SUPERVISOR_H

#include "DriveConfig.h"
#include "ServoController.h"

class LegSupervisor {
public:
    explicit LegSupervisor(const ServoConfig& ServoCFG);

    bool begin();  // Initializes the servo LEDC
    void captureInitialAngle(uint16_t raw_mv);  // Converts voltage to angle and injects it
    float getCurrentAngle() const;             // Returns current angle from servo
    void setSteeringAngle(float angle);
    void setRawSteeringAngle(float angle);
private:
    ServoController servo_;

    bool attachLEDC(const LEDCConfig& cfg);
};

#endif //LEG_SUPERVISOR_H