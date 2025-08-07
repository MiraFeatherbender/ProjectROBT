# Project Goals and Next Steps

**Project Progress Overview**

**Total Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 35% | In Progress: 37% | Not Started: 28%

**Goals Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜  
Complete: 47% | In Progress: 42% | Not Started: 11%

**Next Steps Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 32% | In Progress: 36% | Not Started: 33%

## Task State Legend

- [ ] Not started
- [⏳] In progress
- [😰] In progress (stuck or stressful)
- [🧩] Blocked / Needs input
- [🚩] Needs attention / High priority
- [x] Complete

---

## Goals

**Control Dynamics & Hardware**
- [x] Implement hardware-based node addressing via address pins (unified firmware for all legs)
- [x] Support advanced broadcast AT command payloads with per-node and all-node parameter blocks
- [ ] Implement stepper controller module
- [⏳] Integrate servo and stepper motion into custom AT command interface
- [x] Replace static LEDC fade time calculation with parameterized slew time
    - [x] Refactor fade time logic in ServoController to accept direct values from commands, shifting safety responsibility to command logic
    - [ ] Ensure Drive Coordinator project implements angular steering velocity safety checks to prevent unsafe servo

**Command System & Parser**
- [x] Ensure command parser is modular and future-proof for new command types and parameter formats
- [x] Refactor command processing to strip AT+ from cmd.command and parse '='/'?' into a cmd.type field (set/query)
- [⏳] Define and document a `LegControllerCommandMap` for all supported commands
    - [⏳] Ensure all commands use consistent parameter mapping and error code conventions
    - [⏳] Maintain a central documentation standard for each command (name, parameters, responses, error codes)

**Calibration & Storage**
- [⏳] Add flash storage for calibration data, including center pulse time and backlash offset

**Safety & Interlocks**
- [x] Implement interlocks: E-stop overrides all, calibration blocks movement, and both require specific states/modes
- [x] Restrict access to critical commands in maintenance mode
    - [x] Only allow entering maintenance mode when safely parked

**Communications & Migration**
- [⏳] Migrate ESP-NOW and OTAUpdater from anchor node codebase (serial command interface complete; see [migration plan](./ESP-NOW_Command_OTA_Migration_Plan.md))

**Response Consistency**
- [⏳] Ensure all command responses are terse, consistent, and include error codes
    - [⏳] Ensure query responses are always in a consistent, parseable format

---

## Next Steps

**Command System & Parser**
- [x] Implement and test serial AT command input and parsing pipeline (now supports robust unicast and broadcast parsing)
- [x] Add or update unit tests for `parseParams` and `filterNodeParams`
- [x] Review and refactor other modules (e.g., LegSupervisor, NVSManager) for compatibility with new command parser logic
- [⏳] Implement AT command handlers
    - [x] MOVE command handler
    - [x] SMOOTH_STOP command handler
    - [x] PARK command handler
    - [x] HOME command handler
    - [⏳] E_STOP command handler
    - [⏳] SERVO_CAL command handler
    - [⏳] VERIFY_NVS command handler
    - [⏳] NODE command handler
    - [⏳] OTA command handler
- [ ] Add Query support for all commands
    - [ ] MOVE query
    - [ ] SMOOTH_STOP query
    - [ ] PARK query
    - [ ] HOME query
    - [ ] E_STOP query
    - [ ] SERVO_CAL query
    - [ ] VERIFY_NVS query
    - [ ] NODE query
    - [ ] OTA query
- [⏳] Document AT command and broadcast payload formats in code and docs (documentation after implementation)

**Control Dynamics & Hardware**

- [x] Test and validate broadcast message parsing
    - [x] Per-node payloads (e.g., `N11,42,99,|`)
    - [x] All-node payloads (no node tags)
    - [x] Edge cases (missing node, empty payload, malformed input)
- [ ] Implement stepper controller module
    - [ ] Integrate wheel context (position, velocity, acceleration tracking)
    - [ ] Support S-curve profiling for smooth stepper motion
    - [ ] Integrate with command and state machine architecture for modular control
    - [ ] Support synchronized slew time (from Drive Controller project)
- [ ] Add physical reset switch for E-Stop state
    - [ ] Measure pins 8 and 9 for boot state

**Calibration & Storage**
- [ ] Implement flash write and read routines for calibration data
    - [ ] NVS based. Use "SweepProfile"
    - [ ] Test boot-time retrieval of calibration data
    - [x] Move "SweepProfile" to independent "FlashStorageTypes.h"
    - [⏳] Implement SweepProfile transfer flow:
        - [⏳] ServoCalibration creates SweepSummary
        - [⏳] LegSupervisor relays SweepSummary to NVSManager via getter
        - [⏳] NVSManager accepts SweepSummary from LegSupervisor to store in flash

**Documentation & Testing**
- [⏳] Document all commands
    - [⏳] MOVE documentation
    - [⏳] SMOOTH_STOP documentation
    - [⏳] PARK documentation
    - [⏳] HOME documentation
    - [⏳] E_STOP documentation
    - [⏳] SERVO_CAL documentation
    - [⏳] VERIFY_NVS documentation
    - [⏳] NODE documentation
    - [⏳] OTA documentation
- [ ] Update documentation and code comments for new/changed commands and error codes
- [ ] Add diagnostic/test commands for hardware and storage modules
- [ ] Integrate servo calibration triggers into custom AT command interface
- [x] Write unit tests for command dispatcher and registration logic
- [x] Implement dynamic command registration in CommandDispatcher (optional)
- [ ] Develop mock modules for test builds

**State Machine & Supervisory Logic**
- [x] Prototype SystemState state machine in LegSupervisor
    - [⏳] Implement Booting state
    - [x] Implement Home state
    - [x] Implement Parked state
    - [x] Implement Stopped state
    - [x] Implement ProcessMoveCMD state
    - [x] Implement Moving state
    - [⏳] Implement Calibrating state
    - [⏳] Implement EStop state
    - [⏳] Implement Maintenance state
    - [⏳] Implement Updating state
- [x] Refactor boot logic from *begin() to state machine
    - [x] Servo startup position belongs in homing state
- [x] Implement HOME command for external use and internal self injection

