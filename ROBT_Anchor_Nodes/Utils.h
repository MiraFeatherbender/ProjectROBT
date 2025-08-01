#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <esp_wifi.h>
#include "ExternDefinitions.h"

void readMacAddress(uint8_t* baseMac);
void computeDelayWindow(const uint8_t* baseMac, uint16_t &windowStart, uint16_t &windowEnd);
void applyRandomDelay(uint16_t windowStart, uint16_t windowEnd);
void hardResetUWBSensor();
// Reads the sensor response from Serial1 and returns it.
String receiveSensorResponse();

// Generic retry operation utility
bool retryOperation(std::function<bool()> operation, int maxRetries, int delayMs = 10);
// Attempt to execute custom command with parameters.
bool executeCommand(const String& commandName, const std::vector<String>& params = {""}, String* customReturn = nullptr);
#endif  // UTILS_H
