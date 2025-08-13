# Goals & Steps (Phase-Aligned)

**Version:** 2025-08-12

---

## Project Progress Overview

**Total Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜  
Complete: 45% | In Progress: 30% | Not Started: 25%

**Goals Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 33% | In Progress: 33% | Not Started: 33%

**Next Steps Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜  
Complete: 46% | In Progress: 29% | Not Started: 25%

## Task State Legend

- [ ] Not started
- [⏳] In progress
- [😰] In progress (stuck or stressful)
- [🧩] Blocked / Needs input
- [🚩] Needs attention / High priority
- [x] Complete

---

## Goals

- [x] **Complete Servo Calibration Pipeline** *(File Group 1: Calibration Pipeline)*
- [⏳] **Finalize Command System Implementation** *(File Group 2: Command System)*
- [x] **Integrate State Machine & Supervisor** *(File Group 3: State Machine & Supervisor)*
- [x] **Establish Persistent Storage** *(File Group 4: Persistent Storage)*
- [⏳] **Refine Hardware Abstraction Layer** *(File Group 5: Hardware Abstraction)*
- [ ] **Migrate ESP-NOW Communication** *(File Group 2, 5: Command System, Hardware Abstraction)*
- [ ] **Implement OTA Update System** *(File Group 2, 5: Command System, Hardware Abstraction)*
- [⏳] **Update Documentation & Onboarding** *(File Group 6: Documentation & Onboarding)*
- [ ] **Wireless Infrastructure & Network Coordination** *(File Group 2, 5: Command System, Hardware Abstraction)*

---

## Next Steps

### For: Complete Servo Calibration Pipeline

- [ ] Document calibration workflow

### For: Finalize Command System Implementation

- [⏳] Command System Core
  - [⏳] Maintain a central documentation standard for each command
  - [ ] Add missing command definitions
- [⏳] Command Handlers
  - [⏳] Modular differentiation of action, set, and query modes
    - [⏳] Add query support:
      - [⏳] MOVE
      - [⏳] CAL
- [⏳] Safety & Consistency
  - [⏳] Implement universal error code map for consistent error responses
  - [⏳] Ensure all command responses are terse, consistent, and include error codes
    - [ ] Include error codes
- [⏳] Documentation
  - [⏳] Document AT command and broadcast payload formats in code and docs
    - [⏳] MOVE documentation
    - [⏳] SMOOTH_STOP documentation
    - [⏳] PARK documentation
    - [⏳] HOME documentation
    - [⏳] E_STOP documentation
    - [⏳] CAL documentation
    - [⏳] NODE documentation
    - [⏳] OTA documentation

### For: Integrate State Machine & Supervisor

### For: Establish Persistent Storage

- [⏳] Persistent Storage & Serialization
  - [⏳] Ensure persistent storage of calibration data via `NVSManager`
  - [⏳] Expand use of template-based storage and serialization for persistent data
  - [⏳] Validate serialization/deserialization logic for calibration summaries
  - [⏳] Add diagnostic/test commands for hardware and storage modules
- [⏳] Finalize and validate flash storage routines for calibration data, including boot-time retrieval and integrity checks

### For: Refine Hardware Abstraction Layer

- [⏳] Hardware Modules
  - [⏳] Review and optimize:
    - [⏳] DriveConfig
    - [⏳] HallSensorHandler
    - [⏳] ServoController
    - [⏳] StepperController
  - [ ] Add inline comments for hardware logic
  - [ ] Test hardware abstraction with real devices
- [⏳] Stepper Controller Integration
  - [⏳] Implement stepper controller module
    - [🧩] Integrate servo and stepper motion into custom AT command interface
- [ ] Ensure Drive Coordinator project implements angular steering velocity safety checks

### For: Migrate ESP-NOW Communication

- [⏳] Migrate ESP-NOW and OTAUpdater from anchor node codebase
- [ ] Design migration plan for ESP-NOW protocol
- [ ] Implement ESP-NOW handlers in relevant modules:
  - [ ] Anchor Nodes
  - [ ] Leg Controller
  - [ ] Central Coordinator
- [ ] Validate communication reliability

### For: Implement OTA Update System

- [ ] Design OTA update workflow
- [ ] Integrate OTA logic into command system
- [ ] Test OTA update process
  - [ ] Validate OTA triggers via AT command
  - [ ] Test OTA update on all node types
  - [ ] Document OTA update process

### For: Update Documentation & Onboarding

- [⏳] Review and update `Project_Context.md`, onboarding guides
- [ ] Add missing documentation for new modules
- [ ] Standardize formatting across docs
- [ ] Develop mock modules for test builds
- [ ] Refine broadcast message parsing and payload validation for edge cases
- [ ] Review and resolve blocked/high-priority checklist items before starting new features

### For: Wireless Infrastructure & Network Coordination

- [ ] Implement Modular Communication Manager class
  - [ ] Support runtime switching between ESP-NOW and WiFi Station mode
  - [ ] Maintain MAC address table and device registry
  - [ ] Synchronize mode changes across all devices
- [ ] Integrate debugging workflow (WiFi Station mode, TCP/IP logging)
- [ ] Implement security/authentication for remote connections
- [ ] Document integration patterns for UWB, anchor nodes, and central coordinator
- [ ] Test wireless mode switching and reliability

---

### Archive

#### 1. Complete Servo Calibration Pipeline

- Persistent Storage & Serialization
  - [x] Add flash storage for calibration data, including center pulse time, backlash offset, fit results, and per-magnet residuals
- Calibration Logic & Validation
  - [x] Complete servo calibration and verify results
  - [x] Troubleshoot and verify calibration pipeline:
    - [x] Diagnose Hall sensor ISR event propagation
    - [x] Debug sweep event mapping and PWM-to-magnet index logic
    - [x] Fix calibration summary calculation and state handling
    - [x] Add and interpret debug prints for sweep arrays and summary struct
    - [x] Correct summary validation flag assignment
    - [x] Confirm event-to-summary traceability
    - [x] Document troubleshooting steps and lessons learned
  - [x] Review and validate calibration logic in `ServoCalibration.cpp/h`

#### 2. Finalize Command System Implementation

- Command System Core
  - [x] Audit command parsing and dispatch in `CommandFactory`, `CommandParser`, `CommandDispatcher`  
  - [x] Test serial input handling
  - [x] Ensure command parser is modular and future-proof for new command types and parameter formats
  - [x] Refactor command processing to strip AT+ from cmd.command and parse '='/'?' into a cmd.type field
  - [x] Define and document a `CommandFactory` for all supported commands
  - [x] Ensure all commands use consistent parameter mapping and error code conventions

- Safety & Consistency
  - [x] Implement default error responses (`+ERR:UNSUPPORTED_COMMAND_MODE`)
  - [x] Implement interlocks: E-stop overrides all, calibration blocks movement, and both require specific states/modes
  - [x] Restrict access to critical commands in maintenance mode
  - [x] Only allow entering maintenance mode when safely parked
  - [x] Ensure query responses are always in a consistent, parseable format
  
- Ensure all command responses are terse, consistent, and include error codes
  - [x] Terse and consistent
  
- Modular differentiation of action, set, and query modes
  - Add query support
    - [x] SMOOTH_STOP
    - [x] PARK
    - [x] HOME
    - [x] E_STOP
    - [x] NODE
  - [x] Implement command handlers:
    - [x] MOVE
    - [x] SMOOTH_STOP
    - [x] PARK
    - [x] HOME
    - [x] E_STOP
    - [x] CAL
    - [x] OTA
- [x] Add slew parameter support to SMOOTH_STOP command
- [x] Refactor commands to use unified handlers, supporting action, set, and query modes
- [x] Reassign the "VERIFY_NVS" command to be handled as the calibration query mode

#### 3. Integrate State Machine & Supervisor

- [x] Prototype SystemState state machine in LegSupervisor
- [x] Refactor boot logic from *begin() to state machine
- [x] Implement HOME command for external use and internal self injection
- [x] Refactor state transitions in `LegSupervisor` and `ROBT_Leg_Controller.ino`

#### 4. Establish Persistent Storage

- [x] Implement NVSManager and FlashStorageTypes
- [x] Validate data retention across reboots
- [x] Add flash storage for calibration data

#### 5. Refine Hardware Abstraction Layer

- Hardware Modules
- [x] Node Addressing & Broadcast
  - [x] Implement hardware-based node addressing via address pins
  - [x] Support advanced broadcast AT command payloads with per-node and all-node parameter blocks
- [x] Servo Slew & Fade
  - [x] Replace static LEDC fade time calculation with parameterized slew time
  - [x] Refactor fade time logic in ServoController to accept direct values from commands

#### 6. Migrate ESP-NOW Communication

#### 7. Implement OTA Update System

#### 8. Update Documentation & Onboarding

- [x] Archive legacy files and update documentation to reflect new modular practices
- [x] Expand onboarding and context documentation to reference new file groups and archiving practices
- [x] Expand onboarding documentation to clarify agent-driven review and fallback patch process
- [x] Add explicit workflow step for agent to present actionable suggestions and code blocks when automation fails
- [x] Write unit tests for command dispatcher and registration logic
- [x] Implement dynamic command registration in CommandDispatcher (optional)

#### 9. Wireless Infrastructure & Network Coordination
