# Copilot Onboarding

Welcome, Copilot (or collaborator)! This project uses modular C++ for an ESP32-based robotic leg controller. Please read this file top-to-bottom before making suggestions or edits.

---

## Table of Contents

- [Project Context Reference](#project-context-reference)
- [Development Environment](#development-environment)
- [Hardware Overview](#hardware-overview)
- [Calibration Pipeline](#calibration-pipeline)
- [AT Command System](#at-command-system)
- [Project Structure](#project-structure)
- [Communication Interfaces](#communication-interfaces)
- [Persistent Storage](#persistent-storage)
- [Coding Style & Preferences](#coding-style--preferences)
- [Testing & Debugging](#testing--debugging)
- [Documentation & Archive](#documentation--archive)
- [Known Issues, Constraints, and Preferences](#known-issues-constraints-and-preferences)
- [Recent Changes](#recent-changes)
- [Goals & Next Steps](#goals--next-steps)
- [How to Run / Build](#how-to-run--build)
- [Migration & Goals Reference](#migration--goals-reference)

---

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

 **Main MCU:** 11x ESP32-C3 Super Mini
 **Parent MCUs:** 2–3x Unexpected Maker FeatherS3 modules (ESP-NOW network)
 **Peripherals:**

- 6x 30kg·cm servo motors (one per leg)
- 6x custom dual edge detection hall sensor circuits (servo calibration)
- 6x NEMA23 stepper motors
  - **Drivers:** 6x DM542T Full Digital Stepper Drivers
- 6x steel rods (8mm × 100mm, one per leg)
- Various sensors (see module docs)
- Power wiring and distribution
- 2x 12V 25Ah LiFePO4 batteries (main power, ~2.86 kg each)

### Hardware Weight Breakdown (Estimated)

 | Component                        | Quantity | Unit Weight (kg) | Total Weight (kg) |
 |-----------------------------------|----------|------------------|-------------------|
 | NEMA23 Stepper Motor              | 6        | 0.75             | 4.50              |
 | DM542T Stepper Driver             | 6        | 0.20 (est.)      | 1.20              |
 | ESP32-C3 Super Mini               | 11       | 0.01 (est.)      | 0.11              |
 | UM FeatherS3                      | 2–3      | 0.02 (est.)      | 0.04–0.06         |
 | 30kg·cm Servo                     | 6        | 0.06 (est.)      | 0.36              |
 | Steel Rod (8mm × 100mm)           | 6        | 0.40 (est.)      | 2.40              |
 | LiFePO4 Battery (12V 25Ah)        | 2        | 2.86             | 5.72              |
 | Sensors, Wiring, Chassis, Wheels  | —        | —                | 4.00 (est.)       |
 | **Estimated Total**               |          |                  | **18.33–18.35**   |

 *All weights are approximate. Update as needed for final build.*

### Performance Summary (Torque & Velocity)

 | Scenario      | Motor PPS | Motor Torque (N·m) | Max Mass (kg) | Velocity (m/s) |
 |---------------|-----------|--------------------|---------------|---------------|
 | Flat Land     | 5000      | 0.5                | >18.3         | 1.28          |
 | Curb Climb    | 1000      | 1.1                | 18.3          | 0.26          |

 *For curb climbing, reduce speed (PPS) to maximize available torque. For flatland, higher speeds are possible with ample torque margin.*

### Timer & Driver Settings

- Hardware Timer pulse_us reference: 1M/PPS
- Microstepping: 400 microsteps/rev (DM542T DIP SW5–SW8: OFF, ON, ON, ON)
- Gear ratio: 0.25 (4:1)
- Wheel diameter: 130 mm (circumference ≈ 408.41 mm)
- Stepper: NEMA23, 1.8°/step
- Maximum velocity: 1.7 m/s
- Maximum PPS: 6,667Hz

### Microstep Resolution (SW5–SW8)

| Steps/rev (1.8° motor) | SW5 | SW6 | SW7 | SW8 |
|-----------------------|------|------|------|------|
| 400                   | OFF  | ON   | ON   | ON   |
| 800                   | ON   | OFF  | ON   | ON   |
| 1600                  | OFF  | OFF  | ON   | ON   |
| 3200                  | ON   | ON   | OFF  | ON   |
| 6400                  | OFF  | ON   | OFF  | ON   |
| 12800                 | ON   | OFF  | OFF  | ON   |
| 25600                 | OFF  | OFF  | OFF  | ON   |
| 1000                  | ON   | ON   | ON   | OFF  |
| 2000                  | OFF  | ON   | ON   | OFF  |
| 4000                  | ON   | OFF  | ON   | OFF  |
| 5000                  | OFF  | OFF  | ON   | OFF  |
| 8000                  | ON   | ON   | OFF  | OFF  |
| 10000                 | OFF  | ON   | OFF  | OFF  |
| 20000                 | ON   | OFF  | OFF  | OFF  |
| 25000                 | OFF  | OFF  | OFF  | OFF  |

### Dynamic Current Setting (SW1–SW3)

| Peak Current | RMS Current | SW1 | SW2 | SW3 |
|--------------|-------------|------|------|------|
| 1.00A        | 0.71A       | ON   | ON   | ON   |
| 1.46A        | 1.04A       | OFF  | ON   | ON   |
| 1.91A        | 1.36A       | ON   | OFF  | ON   |
| 2.37A        | 1.69A       | OFF  | OFF  | ON   |
| 2.84A        | 2.03A       | ON   | ON   | OFF  |
| 3.31A        | 2.36A       | OFF  | ON   | OFF  |
| 3.76A        | 2.69A       | ON   | OFF  | OFF  |
| 4.20A        | 3.00A       | OFF  | OFF  | OFF  |

## Usage Overview

- Follow the steps in the README "Getting Started" section for initial setup.
- On boot, the firmware samples the servo potentiometer via ADC, calibrates using hall sensor feedback, and sets node address from digital pins.
- Use the Serial Monitor for debugging and status messages.
- For hardware setup, refer to "Hardware Overview" and "Pin Assignments" above.
- For troubleshooting, see "Known Issues" and "Troubleshooting" below.
  - LED indicators (for diagnostics and hardware-in-the-loop testing)
- **Pin Assignments:** Defined in DriveConfig.h and README.md
- **Node Addressing:** Node address is set via three digital input pins (see DriveConfig.h and ROBT_Leg_Controller.ino), read at startup and used to set the node number in CommandParser.
- **ADC Usage:** ADC is used for servo potentiometer at boot, then deinitialized; address selection uses digital pins only.

---

## Calibration Pipeline

- Via AT+CAL command the system sweeps the servo and uses hall sensor feedback to detect magnet positions.
- Calibration logic is modular, with results stored in a summary struct and saved to NVS using NVSManager.h.
- Automatic backlash compensation is applied based on calibration results.
- For implementation details, see `ServoCalibration.cpp/h`, `FlashStorageTypes.h/cpp`, `NVSManager.h`, and `LegSupervisor.cpp/h`.
- Troubleshooting: If calibration does not complete, check hall sensor wiring, magnet placement, and review serial output for missed events or storage errors.

---

## AT Command System

- All AT commands are registered and dispatched using the modular `CommandFactory`, `CommandParser`, and `CommandDispatcher` system.
- Commands support unified response patterns: `+OK` for success, `+ERR:<code>` for errors.
- For a full list of commands, parameters, and responses, see the README "AT Command Reference" section.
- Error codes are documented below and updated as new codes are added.
- For onboarding, usage, and troubleshooting, refer to the relevant sections above.
- Planned/experimental commands (e.g., stepper control, OTA) are listed as appropriate.

---

## Project Structure

- **Main Entry Point:** ROBT_Leg_Controller.ino (Arduino sketch)
- **Key Modules:**
  - DriveConfig.h: Pin assignments, hardware details, and config structs
  - HallSensorHandler: ISR for hall sensor triggers during calibration
  - LegSupervisor: System manager and main control class
  - NVSManager.h: Header-only, template-based non-volatile memory read/write (legacy NVSManager.cpp archived)
  - FlashStorageTypes.h/cpp: Modular types and serialization for calibration data (new)
  - ServoCalibration: Manages servo calibration using hall sensor feedback
  - ServoController: Commands and tracks servo position
  - CommandDispatcher: Centralized dispatcher for mapping command strings to handlers
  - CommandFactory: Centralized registration and differentiation of AT command handlers by mode (action, set, query)
  - CommandParser: Parses input lines into ParsedCommand, strips AT+ and classifies type. Now supports setting the node number after construction, allowing address pins to be read after pin initialization.
  - ParsedCommand: Struct representing a parsed AT command, including command, type, params, and context
  - SerialInputHandler: Handles serial input and provides CommandSourceContext for responses
  - (Planned) StepperController: Will manage NEMA23 stepper motor
- **File Organization:** All logic is in .cpp/.h files, with configuration and hardware abstraction separated for clarity.
- **Archived Files:** NVSManager.cpp (legacy, see archive folder for historical reference)

- **Automation & Workflow Integration:**
  - **Phase Completion Chat Mode:** `.github/chatmodes/Phase_Completion.chatmode.md` enables Copilot-driven, step-by-step phase completion workflow with dedicated instructions and toolset.
  - **Toolset Manifest:** `phase_completion.toolsets.jsonc` defines a focused set of Copilot tools for review, automation, and archiving.
  - **Workflow Instructions:** `ROBT_Leg_Controller/docs/Automated_Phase_Completion_Workflow.md` and related files provide detailed steps and context for end-of-phase review.
  - **VS Code Tasks:** `.vscode/tasks.json` automates diffing, archiving, and documentation progress bar updates.
  - **Onboarding:** Updated guides and documentation reference the new chat mode and automation features for contributors and Copilot.

---

## Communication Interfaces

- **Current:** Serial (for bench testing)
- **Planned:** ESP-NOW (primary)
- **Protocols/Formats:** Custom AT command syntax

---

## Persistent Storage

- **Type:** ESP32 NVS (Non-Volatile Storage)
- **Stored Data:** Calibration data (using the SweepSummary struct)
- **Storage Flow:** Data is written and retrieved via NVSManager using SweepSummary.
- **Implementation:** NVSManager is now header-only and uses template-based methods for storage, retrieval, and preview. Legacy implementation (`NVSManager.cpp`) is archived in the `archive/` folder for historical reference.
- **Serialization/Deserialization:** Modular serialization and deserialization logic for calibration summaries is implemented in `FlashStorageTypes.cpp`.

---

## Coding Style & Preferences

**Style:**

- Prefer standard C++ style (classes, strong typing, modern idioms) for most of the codebase
- Use Arduino syntax only when necessary (e.g., for main entry point or features not easily done in C++)
- Prefer switch/case statements over if-else chains for state management
- Use minimal or zero nesting in if statements; favor early returns and guard clauses to reduce complexity
**Naming Conventions:**
- Descriptive, camelCase or snake_case for variables and functions
- Structs and classes use PascalCase
- Constants and enums are clearly named and scoped
**Formatting:**
- Consistent indentation and spacing
- Grouped and commented sections for clarity
**Comments:**
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

## Documentation & Archive

- **Documentation:** All major modules and workflows are documented in the `docs` folder. See `Goals_And_Steps.md`, `Project_Context.md`, and workflow files for onboarding and progress tracking.
- **Archive Folder:** Legacy files and milestone reports are archived in `docs/archive/`. Reports are named by milestone/topic for traceability.
- **Recent Additions:** FlashStorageTypes.h/cpp, updated calibration pipeline documentation, milestone-specific phase completion reports.

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

## Recent Changes

Last reviewed by Copilot: August 11, 2025

- Major refactor: Calibration pipeline and persistent storage now use expanded template-based methods in NVSManager for modular, type-safe storage and retrieval
- Modular serialization/deserialization for calibration summaries implemented in `FlashStorageTypes.cpp`
- File group system adopted for targeted review, troubleshooting, and automation
- Command handler and dispatcher refactored to use CommandFactory with boilerplate helper, streamlining new command creation
- All custom AT commands (except OTA) are now ready for use; unified +OK response and error handling pattern implemented
- Documentation and progress tracking updated for automation compatibility and clarity
- Roadmap entry added for universal error code map to support consistent error responses
- Manual and automated edits validated for patch reliability and documentation integrity
- Comments and code structure reviewed and cleaned for maintainability
- NVSManager.cpp archived; all NVS operations now use header-only, template-based methods in NVSManager.h
- Expanded file group mapping and onboarding documentation to reference new archive and modular storage practices

## Goals & Next Steps

- See [Goals_And_Steps.md](Goals_And_Steps.md) for the current development roadmap, progress bars, and milestone verification.
- Current priorities: Complete modular calibration pipeline, expand persistent storage, implement stepper controller, and migrate ESP-NOW/OTA functionality.
- Next steps: Integrate automated review and documentation workflows, expand error code support, and add unit tests.
- Branch for major features, refactors, troubleshooting, and hardware integration.

---

## How to Run / Build

- Open the project folder in **Visual Studio Code**.
- Ensure the **Arduino Extension** is installed and configured.
- Open `ROBT_Leg_Controller.ino` in VS Code.
- Select the **Nologo ESP32-C3 Super Mini** board and correct port in the Arduino Extension.
- Click **Upload** to flash via USB (OTA update planned).
- Use the **Serial Monitor** at 115200 baud for debugging.

*Arduino IDE is supported as a secondary method.*

## Migration & Goals Reference

- See [Goals_And_Steps.md](Goals_And_Steps.md) for current development priorities
- See [ESP-NOW_Command_OTA_Migration_Plan.md](ESP-NOW_Command_OTA_Migration_Plan.md) for migration details
- See [Phase_Completion_Report.md](Phase_Completion_Report.md) for milestone summary and verification details

---
