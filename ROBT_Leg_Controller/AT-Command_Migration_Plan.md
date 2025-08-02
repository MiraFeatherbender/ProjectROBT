# AT Command Migration Plan

This document outlines the step-by-step plan to migrate the serial AT command input and processing system from the ROBT_Anchor_Nodes codebase to the ROBT_Leg_Controller codebase. The goal is to enable robust, extensible serial command handling in the leg controller, similar to the anchor nodes, and to lay the groundwork for future integration with ESP-NOW and OTA features.

---


## Design Summary & Best Practices

### AT Command Migration & Design Summary

**1. Command Structure & Syntax**
- Use the command factory pattern for extensibility.
- Set commands: `AT+COMMAND=param1,param2,...` → `+OK` or `+ERR:<reason>`
- Query commands: `AT+COMMAND?` → `+<data>` or `+ERR:<reason>`
- All responses are terse and machine-parseable; errors always include a reason code.

**2. Command Set**
- Drop anchor node–specific commands.
- Implement leg controller–specific commands (e.g., `AT+MOVE`, `AT+SMOOTH_STOP`, `AT+E_STOP`, `AT+SERVO_CAL`, `AT+VERIFY_NVS`, `AT+PARK`).
- Support both set and query forms where appropriate.

**3. Hardware & State Integration**
- Route all command actions and queries through `LegSupervisor`.
- Let `LegSupervisor` manage state transitions and command validity.
- Use interlocks: E-stop overrides all, calibration blocks movement, and both require specific states/modes.

**4. Security & Access**
- E-stop is always available.
- Maintenance mode restricts access to critical commands (calibration, NVS erase, park).
- Only allow entering maintenance mode when safely parked.
- Design for future ESP-NOW/remote access with these restrictions in mind.

**5. Feedback & Error Reporting**
- Terse, consistent responses for all commands.
- Error codes are always included for system controller parsing.
- Query responses are always in a consistent, parseable format.

**6. Extensibility & Future-Proofing**
- Retain the command factory for easy addition of new commands.
- Design the system to support both serial and ESP-NOW command sources.
- Document standards for new commands (naming, parameters, error codes).
- Plan for group/batch operations: commands include leg IDs, and each leg parses its own section from group messages.


### 1. Review Anchor Node AT Command System
- Study `CustomCommandClasses.*`, `CustomCommandFactory.*`, and serial input loop in `Anchor_Nodes_DualCore_OTA.ino`.
- Identify all dependencies and interactions (e.g., state machine, hardware abstraction).

### 2. Prepare Leg Controller for Serial Input
- Ensure `Serial` is initialized in `ROBT_Leg_Controller.ino`.
- Add a serial input loop (non-blocking, ideally in `loop()` or a dedicated handler).

### 3. Port Command Factory and Classes
- Copy and adapt `CustomCommandClasses.*` and `CustomCommandFactory.*` to `ROBT_Leg_Controller`.
- Refactor as needed for leg controller context (e.g., available hardware, state machine).

### 4. Integrate Command Execution
- Connect serial input loop to command factory for parsing and execution.
- Ensure commands can interact with leg controller classes (e.g., `LegSupervisor`, `ServoController`).

### 5. Test Basic AT Command Handling
- Implement and test basic commands (e.g., `AT+PING`, `AT+HELP`).
- Validate error handling and feedback over serial.

### 6. Extend and Customize Commands
- Add or adapt commands specific to leg controller functionality (e.g., calibration, diagnostics).
- Remove or disable anchor-node-specific commands.

### 7. Document and Refine
- Update documentation and code comments.
- Ensure maintainability and extensibility for future features (e.g., ESP-NOW, OTA).

---

## References
- See `ESP-NOW_Command_OTA_Migration_Plan.md` for related migration steps.
- Anchor node implementation: `ROBT_Anchor_Nodes/CustomCommandClasses.*`, `CustomCommandFactory.*`, `Anchor_Nodes_DualCore_OTA.ino`.
- Leg controller target: `ROBT_Leg_Controller/ROBT_Leg_Controller.ino` and related modules.

---

*Created: August 1, 2025*
