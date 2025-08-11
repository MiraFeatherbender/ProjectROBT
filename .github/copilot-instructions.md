# Leg Controller Calibration Pipeline Copilot Instructions

## Quick Reference
- Main entry: `ROBT_Leg_Controller.ino`
- State machine: `LegSupervisor.*`
- Calibration: `ServoCalibration.*`, `FlashStorageTypes.*`
- AT command system: `CommandFactory.*`, `CommandParser.*`
- Persistent storage: `NVSManager.*`
- Onboarding/context: `docs/Project_Context.md`
- Goals/checklists: `docs/Goals_And_Steps.md`
- Workflow automation: `docs/Automated_Phase_Completion_Workflow.md`

## Integration & Automation
- Build firmware: VS Code Arduino extension, Arduino CLI (`.vscode/tasks.json`)
- Diff/review: "Diff Against Main" VS Code task
- Progress bars: `docs/update_progress.py` (run via VS Code task)
- Phase completion: Follow steps in `docs/Automated_Phase_Completion_Workflow.md`

*For project-wide coding style, review, and documentation standards, see [Leg_Controller_copilot_instructions.md](./Leg_Controller_copilot_instructions.md).*

## Big Picture Architecture
- ESP32-C3-based firmware for modular robotic leg (6-legged rover).
- Major components: Servo control, calibration pipeline, state machine, AT command interface, persistent storage, documentation automation.
- Data flows: Hall sensor ISR → LegSupervisor → ServoCalibration → NVSManager → reporting/diagnostics.
- File group system: All automation, review, and troubleshooting mapped to numbered file groups for targeted analysis.

## Developer Workflow Summary
- **Build**: Use VS Code Arduino extension; select ESP32-C3 Super Mini board.
- **Diff/Review**: Run "Diff Against Main" VS Code task before phase completion.
- **Phase Completion**: Follow `docs/Automated_Phase_Completion_Workflow.md` for review, documentation, and archiving.
- **Progress Bars**: Run "Update Progress Bars" task to refresh documentation indicators.
- **Archiving**: Archive phase completion reports by milestone/topic, not date.

## Project-Specific Conventions
- Reference file groups (see below) in all automation, review, and troubleshooting.
- Use modular, template-based storage and serialization for persistent data.
- Prefer non-blocking state transitions and event-driven design.
- Archive historical files in `archive/` folder; do not reference unless requested.
- Prefer switch statements over if-else chains for state management.
- Prefer early returns and guard clauses to reduce nesting.


## Calibration Pipeline Completion Checklist

Reference file group numbers for targeted review:

- **Hall Sensor ISR Event Pipeline (Groups 1, 2, 3):**
  - Event flow: ISR triggers, SweepEvent creation, event forwarding, sweep logging, calibration validation.
  - Troubleshooting: Confirm ISR firing, validate pattern bits, add serial debug for missed events.
- **Servo Calibration Logic (Group 1):** Modular sweep, fit, residual calculation; store results in summary struct.
- **LegSupervisor Integration (Groups 1, 2):** Relay calibration summary, trigger calibration, collect and store results.
- **NVSManager Storage & Retrieval (Groups 2, 4):** Write/read `SweepSummary` to/from NVS, ensure correct serialization, handle errors.
- **Diagnostic/Reporting (Groups 1, 2, 4):** Print calibration summary and residuals; ensure actionable reporting.
- **Testing (Groups 1, 2, 4):** Test full pipeline with hardware and simulated data.

See file group references below for details.

Use these reference numbers to map checklist headings and discussion topics to the relevant files for each phase:

#### 1. Calibration Pipeline

- `ServoCalibration.cpp` / `ServoCalibration.h` – Calibration logic, state machine, summary creation
- `FlashStorageTypes.h` / `FlashStorageTypes.cpp` – Calibration data structs, fit results, residuals, extensible summary types with static namespace strings

#### 2. State Machine & Supervisory Logic

- `LegSupervisor.cpp` / `LegSupervisor.h` – State machine, context management, pipeline integration
- `ROBT_Leg_Controller.ino` – Main entry, high-level orchestration

#### 3. Command System

- `CommandFactory.cpp` / `CommandFactory.h` – Command registration, CAL handler
- `CommandDispatcher.cpp` / `CommandDispatcher.h` – Command dispatch logic
- `CommandParser.cpp` / `CommandParser.h` – Command parsing, context

#### 4. Persistent Storage (NVS)

- `FlashStorageTypes.h` / `FlashStorageTypes.cpp` – Serialization/deserialization and modular summary support for calibration and future expanded use
- `NVSManager.h` – Header-only, template methods for preview, storage, and retrieval of any summary type using its namespace
- `archive/NVSManager.cpp` – Archived, with comments explaining its deprecation
- `archive/` – Folder for historical files

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

---

## Maintenance Reminder

**Periodic Review:**
After major refactors, phase completions, or onboarding changes, review and update this instructions file to ensure it remains accurate and actionable for AI agents and contributors.

---

## Common Pitfalls & Best Practices

- Always commit all changes before running the diff or phase completion workflow; uncommitted edits will not be included in automation or review.
- Update documentation files (`Project_Context.md`, `Goals_And_Steps.md`, etc.) after any significant code or workflow change to keep onboarding and progress tracking in sync.
- Archive phase completion reports by milestone/topic, not by date, to maintain clear historical context.
- Reference file group numbers in all automation, troubleshooting, and review steps for targeted analysis.
