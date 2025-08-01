#ifndef EXTERNDEFINITIONS_H
#define EXTERNDEFINITIONS_H

#include "OTAUpdater.h"
#include "CustomCommandFactory.h"
#include "CustomCommandClasses.h"
#include "StateMachine.h"
#include "Utils.h"

constexpr int MCU_RX = 20;
constexpr int MCU_TX = 21;
// constexpr uint8_t centralNodeMAC[] = {0xE4, 0xB3, 0x23, 0xC1, 0x40, 0x14};
constexpr uint8_t centralNodeMAC[] = {0xEC, 0xDA, 0x3B, 0x5C, 0x83, 0x54};

// Define command types.
constexpr auto CMD_STANDARD = 0x00;
constexpr auto CMD_OTA      = 0x01;

extern uint8_t baseMac[6];

extern uint16_t windowStart;
extern uint16_t windowEnd;

extern OTAUpdater otaUpdater;
extern StateMachine stateMachine;
extern CustomCommandFactory commandFactory;
#endif //EXTERNDEFINITIONS_H