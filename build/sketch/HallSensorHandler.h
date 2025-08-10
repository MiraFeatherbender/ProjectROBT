#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\HallSensorHandler.h"
#ifndef HALL_SENSOR_HANDLER_H
#define HALL_SENSOR_HANDLER_H

#include <stdint.h>
#include <Arduino.h>
#include "DriveConfig.h"
#include "ServoController.h"
#include "ServoCalibration.h"

class LegSupervisor; // Forward declaration

class HallSensorHandler {
public:
    explicit HallSensorHandler();
    bool begin();

    // Set supervisor for callback
    void setSupervisor(LegSupervisor* supervisor) { supervisor_ = supervisor; }

private:
    static void IRAM_ATTR isrTrampoline();
    void IRAM_ATTR handleISR();

    uint8_t prev_state_;
    uint32_t last_trigger_us_;

    LegSupervisor* supervisor_ = nullptr;
};

#endif // HALL_SENSOR_HANDLER_H