# Project Goals and Next Steps

## Project Progress Overview

**Total Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜  
Complete: 67% | In Progress: 20% | Not Started: 13%

**Goals Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨⬜⬜⬜⬜  
Complete: 71% | In Progress: 18% | Not Started: 11%

**Next Steps Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜  
Complete: 66% | In Progress: 21% | Not Started: 14%

## Task State Legend

- [ ] Not started
- [⏳] In progress
- [😰] In progress (stuck or stressful)
- [🧩] Blocked / Needs input
- [🚩] Needs attention / High priority
- [x] Complete

---

### Branching Guidelines

- Create a branch for any major feature, refactor, or experimental change that:
      - Will take more than a short session to complete
      - Might impact stability or require testing/review
      - Involves architectural changes, new modules, or hardware integration
- Suggested branch naming: `feature/stepper-controller`, `refactor/homing-logic`, `docs/command-updates`, etc.
- Merge back to main only after testing and review.

---

## Goals
  
### Copilot Automation and Workflow Integration

- [x] Automate environment setup and workflow switching for phase completion (Phase Completion chat mode, instructions, and toolset files complete)

### Control Dynamics & Hardware Goals

- [x] Implement hardware-based node addressing via address pins (unified firmware for all legs)
- [x] Support advanced broadcast AT command payloads with per-node and all-node parameter blocks
- [⏳] Implement stepper controller module 🔀
   [🧩] Integrate servo and stepper motion into custom AT command interface 🔀
- [x] Replace static LEDC fade time calculation with parameterized slew time
  - [x] Refactor fade time logic in ServoController to accept direct values from commands, shifting safety responsibility to command logic
- [ ] Ensure Drive Coordinator project implements angular steering velocity safety checks

### Command System & Parser Goals

- [x] Automate status review and checklist updates for phase completion workflow
- [x] Integrate fallback code block system for manual patching in documentation workflow
- [x] Ensure command parser is modular and future-proof for new command types and parameter formats
- [x] Refactor command processing to strip AT+ from cmd.command and parse '='/'?' into a cmd.type field (set/query)
- [x] Define and document a `CommandFactory` for all supported commands 🔀
  - [x] Ensure all commands use consistent parameter mapping and error code conventions
  - [⏳] Maintain a central documentation standard for each command (name, parameters, responses, error codes)
- [x] Ensure command handlers support modular differentiation of action, set, and query modes, following AT command conventions 🔀

### Calibration & Storage Goals

- [x] Complete servo calibration and verify results
- [x] Document calibration data transfer pipeline in both code and markdown (ensure traceability for future audits)
- [x] Add flash storage for calibration data, including center pulse time, backlash offset, fit results, and per-magnet residuals 🔀
- [ ] Finalize and validate flash storage routines for calibration data, including boot-time retrieval and integrity checks
- [⏳] Expand use of template-based storage and serialization for persistent data, supporting future extensibility

### Safety & Interlocks

- [x] Implement interlocks: E-stop overrides all, calibration blocks movement, and both require specific states/modes
- [x] Restrict access to critical commands in maintenance mode
- [x] Only allow entering maintenance mode when safely parked

### Communications & Migration

- [⏳] Migrate ESP-NOW and OTAUpdater from anchor node codebase (serial command interface complete; see [migration plan](./ESP-NOW_Command_OTA_Migration_Plan.md))

### Response Consistency

- [⏳] Ensure all command responses are terse, consistent, and include error codes
  - [x] Terse and consistent
  - [ ] Include error codes
- [x] Ensure query responses are always in a consistent, parseable format

---

## Next Steps
  
### Copilot Automation and Workflow Steps

- [x] Create a dedicated `Phase_Completion.chatmode.md` for Copilot Chat mode
- [x] Draft and maintain a comprehensive instructions file for phase completion workflow
- [x] Develop a curated toolset (`phase_completion.toolsets.jsonc`) for focused automation and review
- [x] Ensure all required documentation files (`Automated_Phase_Completion_Workflow.md`, onboarding, goals, report) are present and referenced
- [x] Integrate VS Code tasks for diffing, archiving, and progress bar updates
- [x] Document onboarding steps for switching to phase completion mode and attaching context
- [ ] Periodically review and update automation files to reflect workflow changes

### Command System & Parser

- [x] Implement and test serial AT command input and parsing pipeline (now supports robust unicast and broadcast parsing)
- [x] Add or update unit tests for `parseParams` and `filterNodeParams`
- [x] Review and refactor other modules (e.g., LegSupervisor, NVSManager) for compatibility with new command parser logic
- [x] Implement AT command handlers 🔀
  - [x] MOVE command handler
  - [x] SMOOTH_STOP command handler
  - [x] PARK command handler
  - [x] HOME command handler
  - [x] E_STOP command handler
  - [x] CAL command handler
  - [x] OTA command handler
- [x] Add slew parameter support to SMOOTH_STOP command 🔀
- [x] Refactor commands to use a unified handlers, supporting action (`CAL`), set (`CAL=...`), and query (`CAL?`) modes 🔀
- [x] Reassign the "VERIFY_NVS" command to be handled as the calibration query mode (`CAL?`) 🔀
- [⏳] Add Query support for appropriate commands 🔀
  - [⏳] MOVE query 🔀
  - [x] SMOOTH_STOP query 🔀
  - [x] PARK query 🔀
  - [x] HOME query 🔀
  - [x] E_STOP query 🔀
  - [⏳] CAL query 🔀
  - [x] NODE query 🔀
- [⏳] Document AT command and broadcast payload formats in code and docs (documentation after implementation) 🔀
- [x] Implement default error responses (`+ERR:UNSUPPORTED_COMMAND_MODE`) for commands that do not support certain modes 🔀
- [⏳] Implement universal error code map for consistent error responses 🔀

### Control Dynamics & Hardware Tasks

- [x] Test and validate broadcast message parsing
  - [x] Per-node payloads (e.g., `N11,42,99,|`)
  - [x] All-node payloads (no node tags)
  - [x] Edge cases (missing node, empty payload, malformed input)
- [🧩] Implement stepper controller module 🔀 (blocked: awaiting servo testing)
  - [ ] Integrate wheel context (position, velocity, acceleration tracking) 🔀
  - [ ] Support S-curve profiling for smooth stepper motion 🔀
  - [ ] Integrate with command and state machine architecture for modular control 🔀
  - [ ] Support synchronized slew time (from Drive Controller project) 🔀
  - [ ] Validate motion profiles and safety interlocks for stepper controller
- [ ] Add physical reset switch for E-Stop state 🔀
  - [ ] Measure pins 8 and 9 for boot state 🔀

### Calibration & Storage

- [x] Troubleshoot and verify calibration pipeline:
  - [x] Diagnose Hall sensor ISR event propagation
  - [x] Debug sweep event mapping and PWM-to-magnet index logic
  - [x] Fix calibration summary calculation and state handling
  - [x] Add and interpret debug prints for sweep arrays and summary struct
  - [x] Correct summary validation flag assignment
  - [x] Confirm event-to-summary traceability
  - [x] Document troubleshooting steps and lessons learned
- [⏳] Implement flash write and read routines for calibration data 🔀
  - [x] NVS based. Use "SweepProfile" 🔀
  - [ ] Test boot-time retrieval of calibration data 🔀
  - [x] Move "SweepProfile" to independent "FlashStorageTypes.h"
  - [x] Implement SweepProfile transfer flow: 🔀
    - [x] ServoCalibration creates SweepSummary (now includes fit results and residuals)
    - [x] LegSupervisor relays SweepSummary to NVSManager via getter (pipeline scaffolded, ready for integration)
    - [x] NVSManager accepts SweepSummary from LegSupervisor to store in flash (print logic in place; ready for full data transfer and storage)
- [⏳] Validate serialization/deserialization logic for calibration summaries in hardware and simulated tests
- [⏳] Add diagnostic/test commands for hardware and storage modules (calibration accuracy and residuals reporting now possible) 🔀
- [x] Expand documentation of calibration pipeline troubleshooting, verification, and lessons learned for traceability

### Documentation & Testing Next Steps

- [x] Archive legacy files and update documentation to reflect new modular practices (e.g., NVSManager.cpp, archive folder)
- [x] Expand onboarding and context documentation to reference new file groups and archiving practices
- [ ] Review and update diagnostic/reporting routines for calibration accuracy and hardware alignment
- [x] Expand onboarding documentation to clarify agent-driven review and fallback patch process
- [x] Add explicit workflow step for agent to present actionable suggestions and code blocks when automation fails
- [⏳] Document all commands
  - [⏳] MOVE documentation
  - [⏳] SMOOTH_STOP documentation
  - [⏳] PARK documentation
  - [⏳] HOME documentation
  - [⏳] E_STOP documentation
  - [⏳] CAL documentation
  - [⏳] NODE documentation
  - [⏳] OTA documentation
- [⏳] Update documentation and code comments for new/changed commands and error codes 🔀
- [⏳] Add diagnostic/test commands for hardware and storage modules 🔀
- [x] Document new calibration fit, residuals, and reporting features
- [x] Integrate servo calibration triggers into custom AT command interface 🔀
- [x] Write unit tests for command dispatcher and registration logic
- [x] Implement dynamic command registration in CommandDispatcher (optional)
- [ ] Develop mock modules for test builds 🔀
- [x] Update onboarding guides to include agent-driven review and explicit workflow steps for actionable suggestions/manual patching
- [ ] Refine broadcast message parsing and payload validation for edge cases
- [ ] Review and resolve blocked/high-priority checklist items before starting new features

### State Machine & Supervisory Logic Next Steps

- [x] Prototype SystemState state machine in LegSupervisor
  - [x] Implement Booting state 🔀
  - [x] Implement Home state
  - [x] Implement Parked state
  - [x] Implement Stopped state
  - [x] Implement ProcessMoveCMD state
  - [x] Implement Moving state
  - [x] Implement Calibrating state 🔀
  - [x] Implement EStop state 🔀
  - [x] Implement Maintenance state 🔀
  - [⏳] Implement Updating state 🔀
- [x] Refactor boot logic from *begin() to state machine
  - [x] Servo startup position belongs in homing state
- [x] Implement HOME command for external use and internal self injection

### State Machine & Supervisory Goals

- [ ] Document and test error handling and state transitions for maintenance/updating states, with unit test coverage
