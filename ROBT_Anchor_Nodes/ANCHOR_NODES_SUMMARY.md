# Anchor Nodes Codebase Summary

## Project Purpose

**ESP32 Arduino Core Version Requirement:**
This codebase is compatible with ESP32 Arduino Core version 3.x and later (ESP-IDF v5.x+), due to updated ESP-NOW callback signatures. Using an older core version will result in compilation errors.

This codebase implements the anchor node firmware for a UWB/ESP-NOW-based localization and communication system. It handles custom AT commands, distance measurement, calibration, and communication with a central node and UWB sensors.

---

## Key Features & Modules
- **CustomCommandClasses.cpp/h:** Implements command classes for distance measurement, calibration, sleep/wake, and hard reset. Each command is registered and executed via a command factory.
- **EspNowHandler.cpp/h:** Handles ESP-NOW initialization, peer management, and message send/receive callbacks.
- **OTAUpdater.cpp/h:** (If present) Handles over-the-air firmware updates.
- **StateMachine.cpp/h:** Manages high-level state transitions and command processing.
- **Utils.cpp/h:** Utility functions for parsing, formatting, and error handling.
- **ExternDefinitions.h:** Shared global variables and definitions.
- **Anchor_Nodes_DualCore_OTA.ino:** Main entry point; sets up hardware, initializes modules, and runs the main loop.

---

## Communication & Protocols
- **ESP-NOW:** Used for wireless communication between anchor nodes and the central node.
- **Serial:** Used for debugging and communication with UWB sensors.
- **Custom AT Commands:** Commands like `AT+MEAS_DISTANCE`, `AT+CAL_RANGE`, `AT+MODE=2`, etc., are parsed and executed by command classes.

---

## Entry Points & Data Flow
- **Main .ino file:** Initializes hardware, sets up ESP-NOW, registers commands, and enters the main loop.
- **Command Execution:** Commands are registered with a factory and executed based on received AT command strings.
- **Distance Measurement:** `DistanceCommand` collects readings, processes them (raw, moving average, gaussian), and sends results via ESP-NOW.
- **Calibration:** `CalRangeCommand` collects and filters readings, computes statistics, and stores calibration results.

---

## Testing & Debugging
- Use Serial output for step-by-step tracing and debugging.
- Use ESP-NOW responses to verify wireless communication.
- Test AT commands via Serial or over-the-air to ensure correct command parsing and execution.

---

## Known Issues / TODOs
- Review and test ESP-NOW peer management for reliability.
- Ensure all command classes are registered and available in the factory.
- Consider adding more robust error handling and response formatting.
- Review calibration and distance measurement logic for edge cases and performance.

---

## Quick Reference
- **Add new commands:** Implement a new class inheriting from the base command, register it in the factory.
- **Debug ESP-NOW:** Check EspNowHandler and Serial output for send/receive status.
- **Update calibration:** Use `AT+CAL_RANGE` and related queries.

---

*This summary is intended to help you quickly navigate and understand the anchor node codebase. Update as needed as the project evolves.*
