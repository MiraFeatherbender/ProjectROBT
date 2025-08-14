# Goals & Steps (Phase-Aligned)
<!-- markdownlint-disable-file MD033 -->
**Version:** 2025-08-12

---

## Project Progress Overview

**Total Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜  
Complete: 49% | In Progress: 26% | Not Started: 25%

**Goals Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 33% | In Progress: 33% | Not Started: 33%

**Next Steps Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜  
Complete: 50% | In Progress: 26% | Not Started: 24%

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

<details>
<summary>For: Complete Servo Calibration Pipeline</summary>

- [ ] Document calibration workflow
- [ ] Enable Hall Sensor Module power control

</details>

<details>
<summary>For: Finalize Command System Implementation</summary>

- [⏳] Command System Core
  - [⏳] Maintain a central documentation standard for each command
  - [ ] Add missing command definitions
- [⏳] Command Handlers
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

</details>

<details>
<summary>For: Integrate State Machine & Supervisor</summary>
</details>

<details>
<summary>For: Establish Persistent Storage</summary>

- [⏳] Persistent Storage & Serialization
  - [⏳] Expand use of template-based storage and serialization for persistent data
  - [⏳] Add diagnostic/test commands for hardware and storage modules
  - [⏳] Finalize and validate flash storage routines for calibration data
    - [ ] Boot-time retrieval
    - [ ] Integrity checks
    - [⏳] Ensure persistent storage of calibration data via `NVSManager`

</details>

<details>
<summary>For: Refine Hardware Abstraction Layer</summary>

- [⏳] Hardware Modules
  - [⏳] Test hardware abstraction with real devices
  - [ ] Add inline comments for hardware logic
  - [⏳] StepperController
    - [ ] Ensure Drive Coordinator project implements angular steering velocity safety checks
    - [🧩] Integrate servo and stepper motion into custom AT command interface
    - [⏳] Implement stepper controller module
      - [⏳] Validate step/dir signal timing and pulse width (≥2.5μs) per DM542T manual
        - [ ]Set PPS to 6,6667 Hz for 1.7m/s drive rate
        - [⏳] Hardware timer setup: Select and configure ESP32 hardware timer (timerBegin, timerAttachInterrupt, timerAlarmWrite) for step pulse generation.
        - [⏳] Pulse interval calculation: Use $\text{alarm\_value} = \frac{1{,}000{,}000}{\text{PPS}}$ to set timer for desired step rate. Reference DM542T driver PPS requirements and minimum pulse width (≥2.5μs).
        - [⏳] Reference ESP32 Arduino Core timer documentation and DM542T manual for timing, interrupt, and reliability best practices.
        - [⏳] Implement PPS based control of velocity/acceleration etc. for linear relationship. 
      - [ ] Link DM542T troubleshooting/FAQ table to hardware test workflow

</details>

<details>
<summary>For: Migrate ESP-NOW Communication</summary>

- [⏳] Migrate ESP-NOW and OTAUpdater from anchor node codebase
- [ ] Implement ESP-NOW handlers in relevant modules:
  - [ ] Anchor Nodes
  - [ ] Leg Controller
  - [ ] Central Coordinator
- [ ] Validate communication reliability

</details>

<details>
<summary>For: Implement OTA Update System</summary>

- [ ] Design OTA update workflow
- [ ] Integrate OTA logic into command system
- [ ] Test OTA update process
  - [ ] Validate OTA triggers via AT command
  - [ ] Test OTA update on all node types
  - [ ] Document OTA update process

</details>

<details>
<summary>For: Update Documentation & Onboarding</summary>

- [ ] Add missing documentation for new modules
- [ ] Standardize formatting across docs
- [ ] Develop mock modules for test builds
- [ ] Refine broadcast message parsing and payload validation for edge cases

</details>

<details>
<summary>For: Wireless Infrastructure & Network Coordination</summary>

- [ ] Implement Modular Communication Manager class
  - [ ] Support runtime switching between ESP-NOW and WiFi Station mode
  - [ ] Maintain MAC address table and device registry
  - [ ] Synchronize mode changes across all devices
- [ ] Integrate debugging workflow (WiFi Station mode, TCP/IP logging)
- [ ] Implement security/authentication for remote connections
- [ ] Document integration patterns for UWB, anchor nodes, and central coordinator
- [ ] Test wireless mode switching and reliability

</details>

---

### Archive

<details>
<summary>1. Complete Servo Calibration Pipeline</summary>

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

</details>

<details>
<summary>2. Finalize Command System Implementation</summary>

- Command System Core
  - [x] Audit command parsing and dispatch in `CommandFactory`, `CommandParser`, `CommandDispatcher`  
  - [x] Test serial input handling
  - [x] Ensure command parser is modular and future-proof for new command types and parameter formats
  - [x] Refactor command processing to strip AT+ from cmd.command and parse '='/'?' into a cmd.type field
  - [x] Define and document a `CommandFactory` for all supported commands
  - [x] Ensure all commands use consistent parameter mapping and error code conventions
  - [x] Implement dynamic command registration in CommandDispatcher (optional)

- Safety & Consistency
  - [x] Implement default error responses (`+ERR:UNSUPPORTED_COMMAND_MODE`)
  - [x] Implement interlocks: E-stop overrides all, calibration blocks movement, and both require specific states/modes
  - [x] Restrict access to critical commands in maintenance mode
  - [x] Only allow entering maintenance mode when safely parked
  - [x] Ensure query responses are always in a consistent, parseable format
  
- Ensure all command responses are terse, consistent, and include error codes
  - [x] Terse and consistent
  
- [x] Modular differentiation of action, set, and query modes
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

</details>

<details>
<summary>3. Integrate State Machine & Supervisor</summary>

- [x] Prototype SystemState state machine in LegSupervisor
- [x] Refactor boot logic from *begin() to state machine
- [x] Implement HOME command for external use and internal self injection
- [x] Refactor state transitions in `LegSupervisor` and `ROBT_Leg_Controller.ino`

</details>

<details>
<summary>4. Establish Persistent Storage</summary>

- Persistent Storage & Serialization
  - Finalize and validate flash storage routines for calibration data, including boot-time retrieval and integrity checks
    - [x] Validate serialization/deserialization logic for calibration summaries
- [x] Implement NVSManager and FlashStorageTypes
- [x] Validate data retention across reboots
- [x] Add flash storage for calibration data

</details>

<details>
<summary>5. Refine Hardware Abstraction Layer</summary>

- Hardware Modules
  - Review and optimize:
    - [x] DriveConfig
    - [x] HallSensorHandler
    - [x] ServoController
- [x] Node Addressing & Broadcast
  - [x] Implement hardware-based node addressing via address pins
  - [x] Support advanced broadcast AT command payloads with per-node and all-node parameter blocks
- [x] Servo Slew & Fade
  - [x] Replace static LEDC fade time calculation with parameterized slew time
  - [x] Refactor fade time logic in ServoController to accept direct values from commands
- Implement stepper controller module
  - [x] Verify power supply voltage and current rating before powering up
  - [x] Physically check and document signal/motor wire separation for noise immunity
  - [x] Document DM542T DIP switch settings for microstep and current
  - [x] Confirm and record standstill current DIP switch (SW4) setting

</details>

<details>
<summary>6. Migrate ESP-NOW Communication</summary>

[x] Design migration plan for ESP-NOW protocol
</details>

<details>
<summary>7. Implement OTA Update System</summary>
</details>

<details>
<summary>8. Update Documentation & Onboarding</summary>

- [x] Review and update `Project_Context.md`, onboarding guides
- [x] Archive legacy files and update documentation to reflect new modular practices
- [x] Expand onboarding and context documentation to reference new file groups and archiving practices
- [x] Expand onboarding documentation to clarify agent-driven review and fallback patch process
- [x] Add explicit workflow step for agent to present actionable suggestions and code blocks when automation fails
- [x] Write unit tests for command dispatcher and registration logic

</details>

<details>
<summary>9. Wireless Infrastructure & Network Coordination</summary>
</details>
