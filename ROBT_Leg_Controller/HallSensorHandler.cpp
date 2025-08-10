#include "HallSensorHandler.h"
#include "soc/gpio_struct.h"
#include "LegSupervisor.h"

static HallSensorHandler* active_handler = nullptr;

HallSensorHandler::HallSensorHandler()
    : prev_state_(0), last_trigger_us_(0), supervisor_(nullptr) {}

void IRAM_ATTR HallSensorHandler::isrTrampoline() {
    if (active_handler) active_handler->handleISR();
}

void IRAM_ATTR HallSensorHandler::handleISR() {
    uint32_t now_us = micros();
    if ((now_us - last_trigger_us_) < 10000) return; // Debounce

    uint16_t gpioState = GPIO.in.val;
    uint8_t curr_state = (gpioState >> PIN_HALL_NORTH) & 0x03;
    if (curr_state == prev_state_) return;

    prev_state_ = curr_state;
    last_trigger_us_ = now_us;

    if (supervisor_) {
        switch (supervisor_->getCalibrationState()) {
            case StateMachine::SWEEP_CW_ACTIVE:
            case StateMachine::SWEEP_CCW_ACTIVE: {
                SweepEvent event;
                event.us_value = supervisor_->getServoPulseUS();
                event.hall_bits = curr_state;
                Serial.println("Hall bits: " + String(curr_state));
                Serial.println("Hall pulse width: " + String(event.us_value));
                supervisor_->handleSweepEventFromISR(event);
                break;
            }
            default:
                // Serial.println("Hall sensor triggered when calibration not ready.");
                break;
        }
    }

}

bool HallSensorHandler::begin() {
    active_handler = this;
    attachInterrupt(digitalPinToInterrupt(PIN_HALL_NORTH), isrTrampoline, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_HALL_SOUTH), isrTrampoline, CHANGE);
    return true;
}