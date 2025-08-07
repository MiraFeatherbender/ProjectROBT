#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\docs\\ESP-NOW_Command_OTA_Migration_Plan.md"
# Migration Plan: Bringing Custom Commands, ESP-NOW, and OTA Updates to ROBT_Leg_Controller

## Overview
This document outlines the steps and considerations for migrating the custom command interface, ESP-NOW communication, and OTA update functionality from the anchor node codebase to the leg controller codebase. The goal is to maintain architectural consistency while adapting features to the leg controller's unique requirements.

---

## 1. Custom Command Interface
- **Files to Adapt:**
  - ~~`CustomCommandClasses.cpp/h`~~
  - ~~`CustomCommandFactory.cpp/h`~~
- **Actions:**
  - ~~Copy the command base class and factory pattern.~~
  - ~~Remove anchor-specific commands; implement leg-controller-specific commands (e.g., servo calibration, diagnostics).~~
  - ~~Register new commands in the factory.~~

**See also:** ~~[AT-Command_Migration_Plan.md](AT-Command_Migration_Plan.md) for a detailed step-by-step plan to migrate the serial AT command input and processing system.~~

## 2. ESP-NOW Communication
- **Files to Adapt:**
  - `EspNowHandler.cpp/h`
  - `ExternDefinitions.h` (as needed)
  - `Utils.cpp/h` (as needed)
- **Actions:**
  - Copy ESP-NOW handler and initialization logic.
  - Adjust peer management and message parsing for the leg controller's role.
  - Update callbacks and payload handling for new commands.
  - Ensure use of updated ESP-NOW callback signatures.

## 3. OTA Updater
- **Files to Adapt:**
  - `OTAUpdater.cpp/h`
- **Actions:**
  - Copy OTA updater module.
  - Integrate into the main `.ino` file and state machine.

## 4. Integration Points
- **Files to Adapt:**
  - `ROBT_Leg_Controller.ino`
  - `StateMachine.cpp/h` (if present)
  - `ExternDefinitions.h`
- **Actions:**
  - Initialize ESP-NOW, OTA, and command factory in setup.
  - Route received ESP-NOW and serial commands to the command factory.
  - Ensure the state machine can handle new command results and OTA events.

## 5. Testing & Debugging
- Add serial and ESP-NOW debug output for new commands and features.
- Test command execution and OTA updates in isolation before full integration.

## 6. Summary Table
| Feature         | Files to Adapt/Copy                | What to Change for Leg Controller                |
|-----------------|-----------------------------------|--------------------------------------------------|
| Custom Commands | CustomCommandClasses.* / Factory.* | Implement new commands, update factory           |
| ESP-NOW         | EspNowHandler.*, Utils.*, Extern*  | Adjust peer roles, message parsing, callbacks    |
| OTA Updater     | OTAUpdater.*                      | Minimal changes, just integrate                  |
| Integration     | .ino, StateMachine.*, Extern*      | Initialize modules, route commands, handle state |

---

## Notes
- Do not begin migration until core interfaces (LegSupervisor, NVSManager, ServoCalibration) are stable.
- Use this plan as a living document; update as needed during migration.
