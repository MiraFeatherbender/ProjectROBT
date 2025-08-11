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
- **LED indicators** (for hardware-in-the-loop testing and diagnostics)

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

_Arduino IDE is supported as a secondary method. If using Arduino IDE, ensure board support and pin assignments match those in `DriveConfig.h`._

---

## Usage

- On boot, the firmware waits for a valid ADC sample, captures the initial servo angle, and enters normal operation.
- The servo is controlled via the `LegSupervisor` and `ServoController` classes.
- Pin modes and assignments are configured in `DriveConfig.h`.
- Hall sensor and magnet sweep logic enable automatic calibration and backlash compensation.
- Node addressing is set via three digital input pins at startup (see `DriveConfig.h` and `ROBT_Leg_Controller.ino`).
- For hardware setup, see the "Hardware Requirements" and "Pinout" sections above.

## Onboarding

- New contributors should start by reading `Project_Context.md` for environment, hardware, and workflow overview.
- Follow the "Getting Started" section above to set up the development environment.
- Review the "Goals & Next Steps" and "Migration & Goals Reference" sections in `Project_Context.md` for current priorities and roadmap.
- For troubleshooting, see the "Troubleshooting" section above and the "Known Issues" section in `Project_Context.md`.
- All major modules and workflows are documented in the `docs` folder.

---

## Calibration

- Calibration is triggered manually via the AT+CAL command.
- The servo performs a sweep, and the dual-edge hall sensor detects magnet positions for precise calibration.
- The calibration pipeline calculates fit and residuals, applies automatic backlash compensation, and stores results in a modular summary struct.
- Calibration data is saved to non-volatile storage using the NVSManager (header-only, template-based).
- For details, see `ServoCalibration.cpp/h`, `FlashStorageTypes.h/cpp`, `NVSManager.h`, and `LegSupervisor.cpp/h`.
- Troubleshooting: If calibration fails (missed hall events, storage errors), check wiring, magnet placement, and review serial output for diagnostic messages.

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

| Command         | Parameters                 | Description                        | Response                |
|-----------------|----------------------------|------------------------------------|-------------------------|
| AT+MOVE?        |                            | Query current move state           | +MOVE? ... / +ERR       |
| AT+MOVE=        | steering, velocity, slew   | Move leg with given params         | +OK / +ERR              |
| AT+SMOOTH_STOP  |                            | Action to 0 in default time, stop  | +OK / +ERR              |
| AT+SMOOTH_STOP? |                            | Query smooth stop state            | +SMOOTH_STOP? ... / +ERR|
| AT+SMOOTH_STOP= | slew                       | Ramp velocity to 0, stop           | +OK / +ERR              |
| AT+E_STOP       |                            | Immediate emergency stop           | +OK / +ERR              |
| AT+E_STOP?      |                            | Query E-Stop state                 | +E_STOP? ... / +ERR     |
| AT+PARK         |                            | Move to park position              | +OK / +ERR              |
| AT+PARK?        |                            | Query park state                   | +PARK? ... / +ERR       |
| AT+HOME         |                            | Move to neutral/home position      | +OK / +ERR              |
| AT+HOME?        |                            | Query home state                   | +HOME? ... / +ERR       |
| AT+CAL          |                            | Start servo calibration            | +OK / +ERR              |
| AT+CAL?         |                            | Query calibration data             | +CAL? ... / +ERR        |
| AT+CAL=         | calibration params         | Set calibration parameters         | +OK / +ERR              |
| AT+NODE?        |                            | Query node assignment              | +NODE? ... / +ERR       |
| AT+OTA          |                            | Begin OTA update                   | +OK / +ERR              |

- All commands use a unified response pattern: `+OK` for success, `+ERR:<code>` for errors.
- The command system is modular, using `CommandFactory`, `CommandParser`, and `CommandDispatcher` for registration, parsing, and dispatch.
- For onboarding, usage, and troubleshooting, see `Project_Context.md`.
- Error codes and descriptions are maintained in the error code reference below.
- Planned/experimental commands (e.g., stepper control, OTA) are listed as appropriate.

### Error Code Reference (Template INW)

| Error Code         | Description (Plain Text)         |
|--------------------|----------------------------------|
| `+ERR:<code>`      | error description                |

_Add error codes and descriptions here as new codes are implemented._

---

## Project Status

- Current focus: Complete NVS data saving/retrieval, implement stepper controller module, verify/refine servo logic, and migrate ESP-NOW functionality and OTA handler.
- Next steps: Integrate automated review prompts and workflows for documentation, command reference, and error code updates.
- Continue expanding handler logic, add unit tests and mock modules, and update documentation/query support as features are completed.
- See [Goals_And_Steps.md](ROBT_Leg_Controller/docs/Goals_And_Steps.md) for detailed roadmap, progress tracking, and milestone verification.

---

## Testing & Debugging

- Use Serial Monitor (115200 baud) for output and debugging.
- Hardware-in-the-loop testing with LED indicators and physical motion.

---

## Troubleshooting

- **USB Device Conflicts:** If VS Code fails to detect the ESP32-C3 board, unplug any non-standard USB devices (e.g., game controllers) and retry.
- **Hall Sensor Wiring:** Ensure hall sensor power and signal wires are correctly connected; use pull-up resistors as shown in wiring diagram.

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
