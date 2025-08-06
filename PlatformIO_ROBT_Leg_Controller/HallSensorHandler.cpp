#include "HallSensorHandler.h"
#include "soc/gpio_struct.h"

static HallSensorHandler* active_handler = nullptr;

HallSensorHandler::HallSensorHandler()
    : prev_state_(0), last_trigger_us_(0) {}

void IRAM_ATTR HallSensorHandler::isrTrampoline() {
    if (active_handler) active_handler->handleISR();
}

void IRAM_ATTR HallSensorHandler::handleISR() {
    uint32_t now_us = micros();
    if ((now_us - last_trigger_us_) < 3000) return; // Debounce

    uint16_t gpioState = GPIO.in.val;
    uint8_t curr_state = (gpioState >> PIN_HALL_NORTH) & 0x03;
    if (curr_state == prev_state_) return;

    prev_state_ = curr_state;
    last_trigger_us_ = now_us;
}

bool HallSensorHandler::begin() {
    active_handler = this;
    attachInterrupt(digitalPinToInterrupt(PIN_HALL_NORTH), isrTrampoline, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_HALL_SOUTH), isrTrampoline, CHANGE);
    return true;
}