# Project Context Reference

This document provides a comprehensive reference for the environment, hardware, structure, and preferences of the ROBT_Leg_Controller project. Use this as a quick guide for Copilot, collaborators, or future development.

---

## Development Environment
- **IDE:** Latest Arduino IDE
- **Board Support:** Latest ESP32 Arduino Core
- **Upload Method:** USB via Arduino IDE (currently); custom HTTP OTA updater (planned, used in other projects)

---

## Hardware Overview
- **Main MCU:** ESP32-C3 Super Mini
- **Planned Network:** Will act as a child MCU to two Unexpected Maker FeatherS3 modules (parents) via ESP-NOW
- **Peripherals:**
  - 1x 30kg servo
  - 1x NEMA23 stepper motor with driver
  - 1x custom dual edge detection hall sensor circuit (for servo direction calibration)
- **Pin Assignments:** Defined in DriveConfig.h and README.md

---

## Project Structure
- **Main Entry Point:** ROBT_Leg_Controller.ino (Arduino sketch)
- **Key Modules:**
  - DriveConfig.h: Pin assignments, hardware details, and config structs
  - HallSensorHandler: ISR for hall sensor triggers during calibration
  - LegSupervisor: System manager and main control class
  - NVSManager: Handles non-volatile memory read/write
  - ServoCalibration: Manages servo calibration using hall sensor feedback
  - ServoController: Commands and tracks servo position
  - CommandDispatcher: Centralized dispatcher for mapping command strings to handlers
  - LegControllerCommandMap: Centralized registration of AT command handlers
  - CommandParser: Parses input lines into ParsedCommand, strips AT+ and classifies type
  - ParsedCommand: Struct representing a parsed AT command, including command, type, params, and context
  - SerialInputHandler: Handles serial input and provides CommandSourceContext for responses
  - (Planned) StepperController: Will manage NEMA23 stepper motor
- **File Organization:** All logic is in .cpp/.h files, with configuration and hardware abstraction separated for clarity.

---

## Communication Interfaces
- **Current:** Serial (for bench testing)
- **Planned:** ESP-NOW (primary), with a custom AT command interface (already developed elsewhere, to be extended here)
- **Protocols/Formats:** Custom AT command syntax

---

## Persistent Storage
- **Type:** ESP32 NVS (Non-Volatile Storage)
- **Stored Data:** Calibration data (using the SweepSummary struct)
- **Storage Flow:** Data is written and retrieved via NVSManager using SweepSummary

---

## Coding Style & Preferences
- **Style:**
  - Prefer standard C++ style (classes, strong typing, modern idioms) for most of the codebase
  - Use Arduino syntax only when necessary (e.g., for main entry point or features not easily done in C++)
- **Naming Conventions:**
  - Descriptive, camelCase or snake_case for variables and functions
  - Structs and classes use PascalCase
  - Constants and enums are clearly named and scoped
- **Formatting:**
  - Consistent indentation and spacing
  - Grouped and commented sections for clarity
- **Comments:**
  - Inline comments for logic explanation
  - Block comments for section headers and struct/class descriptions
  - Comments are clear, concise, and technical

---

## Testing & Debugging
- **Methods:**
  - Serial output for code verification and debugging
  - Hardware-in-the-loop testing (using LED indicators and observing physical motion)
  - Use of Arduino Serial Monitor and Serial Plotter for data visualization
  - No formal test scripts or automated procedures at this time

---

## Known Issues, Constraints, and Preferences
- Uses ESP32 LEDC hardware for both servo (with LEDCfade) and stepper (via frequency adjustment, planned)
- Hall sensor feedback is handled via ISR, used only during calibration
- Avoids blocking calls; prefers state machines for flow control
- Strong preference for switch/case and deterministic math over if statements; minimal or no nested ifs, favoring early returns
- Prefers writing custom libraries for core logic; uses manufacturer or hardware-specific libraries only when necessary (e.g., LCD, SD card)
- Avoids generic libraries (e.g., “servo”) in favor of custom implementations
- No major “gotchas” identified, but design is focused on determinism, maintainability, and hardware efficiency
