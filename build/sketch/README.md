#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\README.md"
# ROBT Leg Controller

Firmware for the ESP32-C3-based robotic wheeled leg, designed for use in a 6-legged disability aid rover.  
Provides robust, safe, and precise steering and drive control with automatic calibration and feedback.

---

## Features

- **Automatic angle calibration** via dual-edge detection hall sensor
- **Direct servo potentiometer sampling** using ADC for startup angle
- **Safe servo startup** and initialization
- **Servo backlash compensation**
- **Modular AT command interface** for robust, extensible control
- **Dynamic hardware-based node addressing** (unified firmware for all legs)
- Modular configuration for servos, steppers, and pin assignments
- **Planned stepper controller support** for advanced motion control

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
2. **Open the project folder in Visual Studio Code**
3. **Install and configure the Arduino Extension**
4. **Open `ROBT_Leg_Controller.ino` in VS Code**
5. **Select the Nologo ESP32-C3 Super Mini board and correct port**
6. **Click Upload to flash via USB (OTA update planned)**
7. **Use the Serial Monitor at 115200 baud for debugging**

_Arduino IDE is supported as a secondary method._

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

The project is organized into modular C++ files for clarity and maintainability. Key files include:

- `ROBT_Leg_Controller.ino` – Main sketch and state machine
- `DriveConfig.h` – Hardware and configuration structs
- `LegSupervisor.cpp/h` – High-level leg/servo management
- `SerialInputHandler.cpp/h` – Serial input buffering and callback pipeline
- `CommandParser.cpp/h` – Serial/ESP-NOW AT command parsing and dispatch
- `CommandFactory.cpp/h` – Centralized AT command registration and mode-differentiated handler sets
- `CommandDispatcher.cpp/h` – Dispatches commands using handler sets from CommandFactory
- `HallSensorHandler.cpp/h` – Hall sensor and magnet sweep logic
- `ServoController.cpp/h` – Servo control logic
- `ServoCalibration.cpp/h` – Servo calibration logic and summary generation
- `FlashStorageTypes.h/cpp` – Modular data structures and serialization for flash storage (new)
- `NVSManager.h` – Header-only, template-based flash storage and calibration data management (legacy `NVSManager.cpp` archived)
- `docs/archive/` – Archived legacy files and milestone reports for traceability

All logic is separated into `.cpp/.h` modules for hardware abstraction and maintainability.

---

## Project Structure

- Modular C++ codebase: hardware, logic, and configuration separated into .cpp/.h modules.
- Main entry: `ROBT_Leg_Controller.ino`
- Key modules: DriveConfig, LegSupervisor, CommandParser, CommandFactory, CommandDispatcher, ServoController, HallSensorHandler, NVSManager, etc.

---

## AT Command Reference

| Command         | Description               |
|-----------------|---------------------------|
| AT+MOVE         | Move leg with parameters  |
| AT+HOME         | Move to home position     |
| AT+SMOOTH_STOP  | Ramp velocity to 0, stop  |
| AT+E_STOP       | Emergency stop            |
| AT+CAL          | Start servo calibration   |
| AT+CAL?         | Verify calibration data   |
| AT+PARK         | Move to park position     |
| AT+NODE         | Responds with node number |
| AT+OTA          | Begin OTA update          |

See `Project_Context.md` for full details.

---

## Project Status

- Major refactor complete, codebase ready for expansion.
- Stepper controller and expanded AT command support planned.
- See [Goals_And_Steps.md](ROBT_Leg_Controller/docs/Goals_And_Steps.md) for roadmap and progress tracking.

---

## Testing & Debugging

- Use Serial Monitor (115200 baud) for output and debugging.
- Hardware-in-the-loop testing with LED indicators and physical motion.

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
