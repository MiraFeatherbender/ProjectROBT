# Copilot Onboarding

Welcome, Copilot (or collaborator)! This project uses modular C++ for an ESP32-based robotic leg controller. Please read this file top-to-bottom before making suggestions or edits. Key context:

- Main entry: `ROBT_Leg_Controller.ino` (Arduino sketch)
- All hardware, config, and logic are separated into .cpp/.h modules
- AT command interface is documented below; see Command Reference
- Node addressing, calibration, and state machine logic are central to operation
- See 'Recent Changes & Current Focus' for what’s actively being developed
- If you need more context, check linked migration and goals docs

## Project Context Reference

This document provides a comprehensive reference for the environment, hardware, structure, and preferences of the ROBT_Leg_Controller project. Use this as a quick guide for Copilot, collaborators, or future development.

---

## Development Environment

- **IDE:** Visual Studio Code with Arduino Extension (primary), Arduino IDE (secondary)
- **Board Support:** Latest ESP32 Arduino Core
- **Upload Method:** USB via VS Code Arduino Extension; Arduino CLI v1.2.2 for compiling and exporting `.bin` files (see `.vscode/tasks.json`)
- **Automation:** VS Code tasks automate firmware builds, CLI upgrades, and documentation progress bar updates. CLI is in the project’s `bin` folder and added to PATH.
- **Documentation Progress Bars:** The `docs/update_progress.py` script updates progress bars in `Goals_And_Steps.md` automatically. It works from either the main project or `docs` folder and is integrated as a VS Code task.

---

## Hardware Overview

- **Main MCU:** ESP32-C3 Super Mini
- **Planned Network:** Will act as a child MCU to two Unexpected Maker FeatherS3 modules (parents) via ESP-NOW
- **Peripherals:**
  - 1x 30kg servo
  - 1x NEMA23 stepper motor with driver
  - 1x custom dual edge detection hall sensor circuit (for servo direction calibration)
- **Pin Assignments:** Defined in DriveConfig.h and README.md
- **Node Addressing:** Node address is set via three digital input pins (see DriveConfig.h and ROBT_Leg_Controller.ino), read at startup and used to set the node number in CommandParser.
- **ADC Usage:** ADC is used for servo potentiometer at boot, then deinitialized; address selection uses digital pins only.

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
  - CommandFactory: Centralized registration and differentiation of AT command handlers by mode (action, set, query)
  - CommandParser: Parses input lines into ParsedCommand, strips AT+ and classifies type. Now supports setting the node number after construction, allowing address pins to be read after pin initialization.
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
- Non-standard USB devices (e.g., game controllers) may cause VS Code to fail to load. Unplug to resolve.

### Common Compiler Error Patterns & Prevention Checklist

- **Enum macro conflicts:** Avoid using names like LOW/HIGH in enums; these may collide with Arduino macros. Always choose unique, descriptive enum values.
- **Missing includes:** If you see 'type not recognized' or 'not declared in this scope' errors, check that all required headers are included in every file that uses those types.
- **Forward declaration issues:** When passing objects between modules, ensure the full class definition is available (not just a forward declaration) in headers where needed.
- **Struct/class definition errors:** Define all structs/classes before use, and keep their definitions in a logical order. If you get 'does not name a type' or brace-enclosed initializer errors, check struct/class visibility and order.
- **Function prototype errors:** Always declare function prototypes in headers for any function used in lambdas, callbacks, or other files. This prevents 'not declared in this scope' errors.
- **Pre-commit hook integration:** If your workflow auto-edits files before commit, make sure your hook stages those changes (e.g., with `git add`) so they're included in the same commit.

Refer to this checklist when adding new features or refactoring code to avoid common build and integration issues.

---

## Recent Changes & Current Focus

Last reviewed by Copilot: August 10, 2025

- Refactored command handler and dispatcher to use CommandFactory with a helper for boilerplate, preserving documentation and streamlining new command creation
- All custom AT commands (except OTA) are now ready for use; unified +OK response and error handling pattern implemented
- Documentation and progress tracking updated for automation compatibility and clarity
- Added roadmap entry for universal error code map to support consistent error responses
- Manual and automated edits validated for patch reliability and documentation integrity
- Comments and code structure reviewed and cleaned for maintainability
- Calibration pipeline troubleshooting, verification, and documentation completed and merged
- Calibration state logic fully integrated into LegSupervisor; summary and diagnostics confirmed
- Progress bars, checklists, and documentation updated to reflect milestone
- Diagnostic and reporting capabilities for calibration accuracy and hardware alignment now operational
- Data pipeline for calibration: SweepSummary is created in ServoCalibration, relayed via LegSupervisor, and ready for storage/printing in NVSManager
- Implemented versatile instruction files for phase-specific guidance and workflow automation
- Added an automated documentation review workflow to streamline end-of-phase updates, consistency checks, and progress tracking
- Coordinated Copilot agent actions and VS Code tasks/scripts for hybrid automation (e.g., progress bar updates, checklist management)
- Began planning for tool sets to support code navigation, diagnostics, and onboarding

Next: Complete NVS data saving/retrieval, implement stepper controller module, verify/refine servo logic, and migrate ESP-NOW functionality
Next: Integrate automated review prompts and workflows for documentation, command reference, and error code updates
Continue expanding handler logic, add unit tests and mock modules, and update documentation/query support as features are completed
Reminder: Branch for major features, refactors, troubleshooting, and hardware integration

---

## How to Run / Build

- Open the project folder in **Visual Studio Code**.
- Ensure the **Arduino Extension** is installed and configured.
- Open `ROBT_Leg_Controller.ino` in VS Code.
- Select the **Nologo ESP32-C3 Super Mini** board and correct port in the Arduino Extension.
- Click **Upload** to flash via USB (OTA update planned).
- Use the **Serial Monitor** at 115200 baud for debugging.

_Arduino IDE is supported as a secondary method._

---

## Command Reference (AT Commands)

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

---

## Migration & Goals Reference

- See [Goals_And_Steps.md](Goals_And_Steps.md) for current development priorities
- See [ESP-NOW_Command_OTA_Migration_Plan.md](ESP-NOW_Command_OTA_Migration_Plan.md) for migration details
- See [Phase_Completion_Report.md](Phase_Completion_Report.md) for milestone summary and verification details

---
