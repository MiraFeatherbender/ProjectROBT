#ifndef HALL_SENSOR_HANDLER_H
#define HALL_SENSOR_HANDLER_H

#include <stdint.h>
#include <Arduino.h>
#include "DriveConfig.h"
#include "ServoController.h"

class HallSensorHandler {
public:
    explicit HallSensorHandler();
    bool begin();

private:
    static void IRAM_ATTR isrTrampoline();
    void IRAM_ATTR handleISR();

    uint8_t prev_state_;
    uint32_t last_trigger_us_;
};

#endif // HALL_SENSOR_HANDLER_H