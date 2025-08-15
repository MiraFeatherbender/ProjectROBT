# Goals & Steps (Phase-Aligned)
<!-- markdownlint-disable-file MD033 -->
**Version:** 2025-08-15

---

## Project Progress Overview

**Total Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 43% | In Progress: 19% | Not Started: 38%

**Goals Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 33% | In Progress: 33% | Not Started: 33%

**Next Steps Progress:**  
🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟨🟨🟨🟨🟨🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜  
Complete: 43% | In Progress: 19% | Not Started: 38%

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

</details>

<details>
<summary>For: Finalize Command System Implementation</summary>

- [x] Command System Core

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
  - [⏳] Maintain a central documentation standard for each command

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
      - [⏳] Validate signal timing and pulse width
        - [ ]Set PPS to <=8000 Hz for 1.2m/s drive rate
        - [⏳] Implement PPS based control of velocity/acceleration etc. for linear relationship.
        - [x] Perform advanced mathematical analysis for movement requirements.
    - [⏳] Implement MKS-TMC2160-OC (SPI Mode)
      - [⏳] Tier 1: Planning, Documentation & Study
        - [x] Compare DM542T and TMC2160 for torque, braking, and control modes
        - [x] Document pin budgeting and SPI requirements for TMC2160
        - [x] Expand pinout table to show legacy and repurposed SPI assignments
        - [x] Analyze passive vs. active braking modes and document engineering context
        - [x] Clarify DIP switch vs. SPI register precedence
        - [x] Reference TMC2160 datasheet for register map and SPI protocol
        - [ ] Review TMC2160 datasheet and MKS board schematic
        - [ ] Identify and document all relevant SPI registers
          - [ ] GCONF  — Global configuration register (enables/disables core features, sets interface modes)
          - [ ] IHOLD_IRUN  — Motor current control (sets run/hold currents and timings)
          - [ ] CHOPCONF  — Chopper configuration (controls microstepping, spreadCycle/stealthChop, blank time, etc.)
          - [ ] DRV_STATUS  — Driver status and diagnostics (reports errors, stall, overtemperature, short detection)
          - [ ] PWMCONF  — PWM mode configuration (controls PWM amplitude, gradient, and switching)
          - [ ] SGTHRS  — StallGuard threshold (sets sensitivity for stall detection and load measurement)
        - [ ] Prioritize register study:
          - [ ] GCONF
          - [ ] IHOLD_IRUN
          - [ ] CHOPCONF
          - [ ] DRV_STATUS
          - [ ] others as needed
      - [ ] Tier 2: Hardware Rewiring & Pin Assignment
        - [x] Map ESP32-C3 Super Mini pins for SPI (MOSI, MISO, SCK, CS)
        - [ ] Desolder/remove Step/Dir-related MOSFETs, transistors, and resistors as needed
        - [ ] Verify PCB traces for SPI signal integrity
        - [ ] Add connector/wiring for each SPI pin (JST or secure Dupont + strain relief)
        - [ ] Document pinout changes in README and schematic
      - [ ] Tier 3: Firmware Boot & SPI Initialization
        - [ ] Implement SPI initialization in firmware (set SPI mode, speed, CS polarity)
        - [ ] On boot, write safe defaults to
          - [ ] GCONF
          - [ ] IHOLD_IRUN
          - [ ] CHOPCONF
        - [ ] Read back DRV_STATUS to confirm communication
        - [ ] Log all SPI transactions for debugging
      - [ ] Tier 4: Feature Enablement & Safety
        - [ ] Enable key features after boot (microstepping, current control, SpreadCycle/StealthChop, StallGuard)
        - [ ] Implement error handling and fallback to DIP switch defaults if SPI fails
        - [ ] Validate braking and motion profile logic with new driver
      - [ ] Tier 5: Testing, Documentation, & Milestones
        - [ ] Test SPI communication and driver response (read/write registers)
        - [ ] Validate stepper motion, torque, and braking performance
        - [ ] Update documentation and onboarding guides for new hardware and firmware
        - [ ] Add troubleshooting steps for SPI wiring, register settings, and driver faults
        - [ ] Milestone: "MKS-TMC2160-OC SPI migration complete, validated, and documented"

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
