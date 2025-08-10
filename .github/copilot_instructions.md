# Leg Controller Calibration Pipeline Copilot Instructions

*For project-wide coding style, review, and documentation standards, see [Leg_Controller_copilot_instructions.md](./Leg_Controller_copilot_instructions.md).*

## Incremental Development and Testing

- Use test modules and serial print statements to validate logic and hardware interactions before implementing full methods.
- Prototype new features or hardware routines with simple, traceable outputs to the serial console.
- Replace placeholders and test code with robust implementations as each stage of the pipeline is validated.
- Document test results and observations in code comments or project notes for future reference.

---

## Calibration Pipeline Completion Checklist

*Reference the group numbers in the Numbered Primary File References by Topic for each subheading below:*

### Hall Sensor ISR Event Pipeline (Groups 1, 2, 3)

- Implement and document the event flow for hall sensor calibration:
  - HallSensorHandler ISR triggers on state change and debounces events (Group 2)
  - ISR constructs a SweepEvent and calls LegSupervisor::handleSweepEventFromISR (Group 1)
  - LegSupervisor forwards the event to ServoCalibration::logSweepEvent for sweep logging and calibration validation (Group 3)
- Troubleshooting steps:
  - Confirm ISR is firing and SweepEvents are generated
  - Validate pattern bits and magnet profile updates in ServoCalibration
  - Add serial debug output for missed events or calibration failures

### Servo Calibration Logic (Group 1)

- Ensure modular calibration routines: sweep, fit, residual calculation.
- Store calibration results (center pulse, backlash, fit coefficients, residuals) in a summary struct (e.g., `SweepSummary`).

### LegSupervisor Integration (Group 1 and 2)

- Relay calibration summary from `ServoCalibration` to `LegSupervisor`.
- Implement logic to trigger calibration, collect results, and prepare for storage.

### NVSManager Storage (Group 2 and 4)

- Implement function to write `SweepSummary` to ESP32 NVS (non-volatile storage).
- Ensure data is serialized/deserialized correctly for storage and retrieval.
- Add error handling for NVS write/read operations.

### NVS Retrieval (Group 2 and 4)

- Implement function to read calibration data from NVS at boot or on demand.
- Validate retrieved data and apply to system (e.g., set servo parameters, update state).

### Diagnostic/Reporting (Group 1, 2, 4)

- Add commands or routines to print calibration summary and residuals for diagnostics.
- Ensure reporting is clear and actionable for hardware alignment and troubleshooting.

### Testing (Groups 1, 2, 4)

- Test full pipeline: calibration → summary creation → NVS storage → NVS retrieval → system update.
- Validate with hardware-in-the-loop and simulated data.

### Numbered Primary File References by Topic

Use these reference numbers to map checklist headings and discussion topics to the relevant files for each phase:

#### 1. Calibration Pipeline

- `ServoCalibration.cpp` / `ServoCalibration.h` – Calibration logic, state machine, summary creation
- `FlashStorageTypes.h` – Calibration data structs, fit results, residuals

#### 2. State Machine & Supervisory Logic

- `LegSupervisor.cpp` / `LegSupervisor.h` – State machine, context management, pipeline integration
- `ROBT_Leg_Controller.ino` – Main entry, high-level orchestration

#### 3. Command System

- `CommandFactory.cpp` / `CommandFactory.h` – Command registration, CAL handler
- `CommandDispatcher.cpp` / `CommandDispatcher.h` – Command dispatch logic
- `CommandParser.cpp` / `CommandParser.h` – Command parsing, context

#### 4. Persistent Storage (NVS)

- `NVSManager.cpp` / `NVSManager.h` – Calibration data storage/retrieval

Reference these numbers in checklists or conversation (e.g., "Focus on group 1 for calibration changes") for targeted analysis and automation.

### Deep Code Investigation Requirement

- When reviewing or automating calibration pipeline or lifecycle logic, always perform deep code tracing. This includes:
  - Tracing all relevant function calls, state transitions, and context/callback flows.
  - Validating that state transitions only occur after true completion of calibration or pipeline phases.
  - Ensuring context is correctly passed, used, and cleared in all relevant modules.
  - Documenting findings and any architectural decisions in code comments or project notes.

### Copilot Agent Workflow for This Phase

- Always prioritize analysis, code tracing, and automation using the relevant numbered file group(s) based on checklist topic or user request.
- If a solution or review requires more context, expand outward from the primary group to related files, and document which groups are being referenced.
- Explicitly mention file group numbers in responses when suggesting changes, reviewing code, or troubleshooting, so the user knows the focus.
- When a checklist item is referenced, automatically map it to the corresponding file group(s) and explain the reasoning.
- After making changes or suggestions, prompt the user to review the relevant file group(s) for consistency and completeness.
- If the primary group does not resolve the issue, inform the user and expand the search to secondary or related groups as needed.
- Tailor automation, code generation, and review strategies to the current phase, using the file group system for targeted actions.
