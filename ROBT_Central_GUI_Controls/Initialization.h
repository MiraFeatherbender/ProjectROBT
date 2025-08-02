#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <Arduino.h>
#include "SerialWrapper.h"         // SerialInterceptor class definition
#include "AiEsp32RotaryEncoder.h"  // Rotary encoder library
#include "robotWindow.h"
#include <UMS3.h>                  // Include board-specific library

// Rotary Encoder Configuration
#define ROTARY_ENCODER_A_PIN 14
#define ROTARY_ENCODER_B_PIN 18
#define ROTARY_ENCODER_BUTTON_PIN 17
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);

// TFT Configuration
#define TFT_CS 1
#define TFT_DC 3
#define TFT_RST 7
#define SD_CS 5
Adafruit_HX8357 tft(TFT_CS, TFT_DC, TFT_RST);
SdFat SD;
Adafruit_ImageReader reader(SD);

GFXcanvas16 robotCanvas(320, 220);

robotWindow robotWindow(tft, robotCanvas, reader);

// Serial Wrapper
SerialInterceptor mirroredSerial(Serial, tft);
#define Serial mirroredSerial  // Redirect Serial to mirroredSerial

// Pin Definitions for Additional Hardware

// Maintained (3-position) switch pins
#define MODE_LEFT_PIN 33
#define MODE_RIGHT_PIN 38
// New momentary switch pins for scan mode (FREERUN/SINGLERUN)
#define SCAN_LEFT_PIN 12
#define SCAN_RIGHT_PIN 11

// Debounce Setting (in ms)
const unsigned long debounceDelay = 200;

// Define a common enum for both switches.
// Here valid states are defined as:
//   1 (binary 01): left side pressed,
//   2 (binary 10): right side pressed,
//   Any other reading (0 or 3) is considered inactive.
enum SwitchState {
  SW_INACTIVE = 0,  // Default or invalid state
  SW_STATE1   = 1,  // Valid: e.g., left press (could correspond to FREERUN for momentary)
  SW_STATE2   = 2   // Valid: e.g., right press (could correspond to SINGLERUN for momentary)
};

// Struct to hold the state of both switches
struct SystemSwitchState {
  SwitchState maintained;
  SwitchState momentary;
};

UMS3 ums3;

//------------------------------------------------------------------------------
// A background task that polls both the maintained and momentary switch states,
// validates the combination, and activates the cycle if valid.
//------------------------------------------------------------------------------
void switchCombinationTask(void *parameters) {
  SystemSwitchState currentState = { SW_INACTIVE, SW_INACTIVE };
  unsigned long lastDebounceTimeMaintained = 0;
  unsigned long lastDebounceTimeMomentary = 0;

  // Helper lambda to map the 2-bit reading to a SwitchState.
  // With INPUT_PULLUP the neutral state yields (HIGH,HIGH) = 1<<1 | 1 == 3;
  // if left is pressed: (LOW,HIGH) = 0<<1 | 1 == 1,
  // if right is pressed: (HIGH,LOW) = 1<<1 | 0 == 2,
  // if both pressed: (LOW,LOW) = 0.
  auto mapSwitchReading = [](int reading) -> SwitchState {
    if (reading == 1) return SW_STATE1;
    else if (reading == 2) return SW_STATE2;
    else return SW_INACTIVE;
  };

  for (;;) {
    // Read both pins for the maintained switch; combine them:
    int maintainedReading = (digitalRead(MODE_LEFT_PIN) << 1) | digitalRead(MODE_RIGHT_PIN);
    int momentaryReading  = (digitalRead(SCAN_LEFT_PIN) << 1) | digitalRead(SCAN_RIGHT_PIN);

    // Map the raw 2-bit values into our defined enum.
    SwitchState newMaintained = mapSwitchReading(maintainedReading);
    SwitchState newMomentary  = mapSwitchReading(momentaryReading);

    unsigned long now = millis();

    // Debounce the maintained switch changes.
    if (newMaintained != currentState.maintained && (now - lastDebounceTimeMaintained >= debounceDelay)) {
      currentState.maintained = newMaintained;
      lastDebounceTimeMaintained = now;
    }
    // Debounce the momentary switch changes.
    if (newMomentary != currentState.momentary && (now - lastDebounceTimeMomentary >= debounceDelay)) {
      currentState.momentary = newMomentary;
      lastDebounceTimeMomentary = now;
    }

    // First, check the maintained switch.
    // It must be in an active state (SW_STATE1 or SW_STATE2); otherwise, do nothing.
    switch (currentState.maintained) {
      case SW_STATE1:
      case SW_STATE2:
        // Valid maintained state; proceed.
        break;
      default:
        // Maintained switch is inactive. Reset momentary to avoid false triggering.
        currentState.momentary = SW_INACTIVE;
        vTaskDelay(pdMS_TO_TICKS(10));
        continue;  // Skip processing further until maintained becomes active.
    }

    // Next, check the momentary switch.
    switch (currentState.momentary) {
      case SW_STATE1:  // Could represent FREERUN.
      case SW_STATE2:  // Could represent SINGLERUN.
      {
        String modeState = currentState.maintained == SW_STATE1 ? "DIRECTION FINDING\n" : "RANGE CALIBRATION\n";
        String scanState = currentState.momentary == SW_STATE1 ? "FREERUN\n" : "SINGLERUN\n";
        // Both switches are in valid states; print the detected state.
        Serial.inject("Maintained State: " + modeState + "Momentary State: " + scanState);

        // Latch the momentary input and simulate a cycle running.
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay for the duration of the cycle.
        Serial.println("Cycle complete... INACTIVE");
        
        // Reset switch soft latch to inactive to prepare for the next cycle.
        currentState.momentary  = SW_INACTIVE;
        break;
      }
      default:
        // Momentary is not pressed (or in a non-valid state); do nothing.
        break;
    }

    // Polling delay.
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

//------------------------------------------------------------------------------
// Hardware initialization revised to include the background switch-combination task.
//------------------------------------------------------------------------------
inline void initializeHardware() {
  ums3.begin();               // Initialize all UM board peripherals
  ums3.setLDO2Power(true);
  
  // TFT Setup
  tft.begin();
  tft.fillScreen(HX8357_BLACK);
  tft.setRotation(2);
  if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) {
    Serial.println(F("SD begin() failed"));
    for(;;);
  }

  robotWindow.begin();

  // Initialize Serial Wrapper
  mirroredSerial.begin(115200);
  
  // Setup pin modes.
  // For the maintained and momentary switches, use INPUT_PULLUP so that neutral reads as HIGH.
  pinMode(MODE_LEFT_PIN, INPUT_PULLUP);
  pinMode(MODE_RIGHT_PIN, INPUT_PULLUP);
  pinMode(SCAN_LEFT_PIN, INPUT_PULLUP);
  pinMode(SCAN_RIGHT_PIN, INPUT_PULLUP);
  
  // Start the background task that polls our switch combinations.
  xTaskCreate(switchCombinationTask,    // Task function
              "SwitchCombinationTask",  // Task name  
              2048,                     // Stack size (in bytes)
              NULL,                     // Parameters
              1,                        // Priority
              NULL);                    // Task handle
}

#endif  // INITIALIZATION_H