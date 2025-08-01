#include "ExternDefinitions.h"

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, MCU_RX, MCU_TX);  // For UWB sensor

  // Initialize ESP‑NOW.
  initEspNow(centralNodeMAC);

  // Read MAC address and compute delay window.
  readMacAddress(baseMac);
  computeDelayWindow(baseMac, windowStart, windowEnd);

  // Reset then sleep the UWB sensor.
  hardResetUWBSensor();
}

void loop() {

  // Update state machine.
  stateMachine.update();
}
