# Leg Controller Calibration Pipeline Copilot Instructions

*For project-wide coding style, review, and documentation standards, see [Leg_Controller_copilot_instructions.md](./Leg_Controller_copilot_instructions.md).*

## Incremental Development and Testing

- Use test modules and serial print statements to validate logic and hardware interactions before implementing full methods.
- Prototype new features or hardware routines with simple, traceable outputs to the serial console.
- Replace placeholders and test code with robust implementations as each stage of the pipeline is validated.
- Document test results and observations in code comments or project notes for future reference.

---

## Calibration Pipeline Completion Checklist

### Servo Calibration Logic

- Ensure modular calibration routines: sweep, fit, residual calculation.
- Store calibration results (center pulse, backlash, fit coefficients, residuals) in a summary struct (e.g., `SweepSummary`).

### LegSupervisor Integration

- Relay calibration summary from `ServoCalibration` to `LegSupervisor`.
- Implement logic to trigger calibration, collect results, and prepare for storage.

### NVSManager Storage

- Implement function to write `SweepSummary` to ESP32 NVS (non-volatile storage).
- Ensure data is serialized/deserialized correctly for storage and retrieval.
- Add error handling for NVS write/read operations.

### NVS Retrieval

- Implement function to read calibration data from NVS at boot or on demand.
- Validate retrieved data and apply to system (e.g., set servo parameters, update state).

### Diagnostic/Reporting

- Add commands or routines to print calibration summary and residuals for diagnostics.
- Ensure reporting is clear and actionable for hardware alignment and troubleshooting.

### Testing

- Test full pipeline: calibration → summary creation → NVS storage → NVS retrieval → system update.
- Validate with hardware-in-the-loop and simulated data.

### Documentation

- Update onboarding and context docs to reflect calibration pipeline, NVS storage, and retrieval process.
- Document commands, error codes, and troubleshooting steps.
