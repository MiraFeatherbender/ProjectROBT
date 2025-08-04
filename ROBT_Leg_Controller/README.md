# ROBT Leg Controller

Firmware for the ESP32-C3-based robotic wheeled leg, designed for use in a 6-legged disability aid rover.  
Provides robust, safe, and precise steering and drive control with automatic calibration and feedback.

---

## Features

- **Automatic angle calibration** via dual-edge detection hall sensor
- **Direct servo potentiometer sampling** using ADC for startup angle
- **Safe servo startup** and initialization
- **Servo backlash compensation**
- Modular configuration for servos, steppers, and pin assignments

---

## Hardware Requirements

- **ESP32-C3 Super Mini** (microcontroller)
- **DSSERVO DS3230MG** (servo)
- **Nema 23 stepper motor** with **DM542 stepper controller**
- **ICL7660s** Voltage Converter
- **LM358** Dual Opamp
- **LM393** Dual Comparator
- Misc. buck converters, N-channel MOSFETs, 2N2222A NPN BJT
- **10x4x2mm neodymium magnets** (7, for hall sensor calibration)

---

## Pinout

| Function                | GPIO Pin | Notes                                 |
|-------------------------|----------|---------------------------------------|
| Servo PWM Output        | 0        | LEDC PWM output to servo signal wire  |
| Servo potentiometer     | 1        | ADC input                             |
| Stepper_DIR             | 2        | Output, low                           |
| Stepper_STEP            | 3        | Output, low                           |
| Hall_Module_PWR         | 4        | Output, high                          |
| Hall_North              | 5        | Input, pull-up                        |
| Hall_South              | 6        | Input, pull-up                        |
| Hall_Module_Indicator   | 7        | Output, high                          |
| Address 1               | 10       | Input, pull-up (MSB)                  |
| Address 2               | 20       | Input, pull-up                        |
| Address 3               | 21       | Input, pull-up (LSB)                  |

---

## Getting Started

1. **Clone this repository**
2. **Install dependencies:**
    - [ESP32 Arduino core](https://github.com/espressif/arduino-esp32) (for Arduino IDE)
3. **Open `ROBT_Leg_Controller.ino` in Arduino IDE**
4. **Select the ESP32-C3 board and correct port**
5. **Build and upload the code**

---

## Usage

- On boot, the firmware waits for a valid ADC sample, captures the initial servo angle, and enters normal operation.
- The servo is controlled via the `LegSupervisor` and `ServoController` classes.
- Pin modes and assignments are configured in `DriveConfig.h`.
- Hall sensor and magnet sweep logic enable automatic calibration and backlash compensation.

---

## Calibration

- The system captures the initial angle from the servo’s potentiometer at startup.
- Dual-edge hall sensor logic enables precise calibration using neodymium magnets.
- Backlash compensation is applied automatically.

---

## File Overview

 - `ROBT_Leg_Controller.ino` – Main sketch and state machine
 - `DriveConfig.h` – Hardware and configuration structs
 - `LegSupervisor.cpp/h` – High-level leg/servo management
 - `SerialInputHandler.cpp/h` – Serial input buffering and callback pipeline
 - `CommandParser.cpp/h` – Serial/ESP-NOW AT command parsing and dispatch
 - `HallSensorHandler.cpp/h` – Hall sensor and magnet sweep logic
 - `ServoController.cpp/h` – Servo control logic
 - `ServoCalibration.cpp/h` – Servo calibration logic and summary generation
 - `FlashStorageTypes.h` – Data structures for flash storage
 - `NVSManager.cpp/h` – Flash storage and calibration data management

---

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0).

> You may use, modify, and share this code for personal and educational purposes only.  
> Commercial use is strictly prohibited.  
> Attribution to Mira Gorum is required for all derivatives.

See [LICENSE](LICENSE) for details.

---

## Credits

Project by **Mira Gorum**

---
