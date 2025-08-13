# ROBT Phase Alignment Workflow Guide

---

## Progress

// ...existing progress section from Goals_And_Steps.md...

## Legend

// ...existing legend section from Goals_And_Steps.md...

---

## Overall Goals (Phase-Aligned)

- [ ] **Complete Servo Calibration Pipeline** *(File Group 1: Calibration Pipeline)*
  - Status: In Progress

- [ ] **Finalize Command System Implementation** *(File Group 2: Command System)*
  - Status: In Progress

- [ ] **Integrate State Machine & Supervisor** *(File Group 3: State Machine & Supervisor)*
  - Status: In Progress

- [ ] **Establish Persistent Storage** *(File Group 4: Persistent Storage)*
  - Status: Done

- [ ] **Refine Hardware Abstraction Layer** *(File Group 5: Hardware Abstraction)*
  - Status: In Progress

- [ ] **Migrate ESP-NOW Communication** *(File Group 2, 5: Command System, Hardware Abstraction)*
  - Status: Not Started

- [ ] **Implement OTA Update System** *(File Group 2, 5: Command System, Hardware Abstraction)*
  - Status: Not Started

- [ ] **Update Documentation & Onboarding** *(File Group 6: Documentation & Onboarding)*
  - Status: In Progress

---

## Next Steps (Action Plan)

### For: Complete Servo Calibration Pipeline

- [ ] Review and validate calibration logic in `ServoCalibration.cpp/h` *(In Progress)*
- [ ] Ensure persistent storage of calibration data via `NVSManager` *(In Progress)*
- [ ] Document calibration workflow *(Not Started)*

### For: Finalize Command System Implementation

- [ ] Audit command parsing and dispatch in `CommandFactory`, `CommandParser`, `CommandDispatcher` *(In Progress)*
- [ ] Add missing command definitions *(Not Started)*
- [ ] Test serial input handling *(In Progress)*

### For: Integrate State Machine & Supervisor

- [ ] Refactor state transitions in `LegSupervisor` and `ROBT_Leg_Controller.ino` *(In Progress)*
- [ ] Add switch/case logic for new states *(Not Started)*
- [ ] Validate supervisor error handling *(Not Started)*

### For: Establish Persistent Storage

- [x] Implement NVSManager and FlashStorageTypes *(Done)*
- [x] Validate data retention across reboots *(Done)*

### For: Refine Hardware Abstraction Layer

- [ ] Review and optimize `DriveConfig`, `HallSensorHandler`, `ServoController`, `StepperController` *(In Progress)*
- [ ] Add inline comments for hardware logic *(Not Started)*
- [ ] Test hardware abstraction with real devices *(Not Started)*

### For: Migrate ESP-NOW Communication

- [ ] Design migration plan for ESP-NOW protocol *(Not Started)*
- [ ] Implement ESP-NOW handlers in relevant modules *(Not Started)*
- [ ] Validate communication reliability *(Not Started)*

### For: Implement OTA Update System

- [ ] Design OTA update workflow *(Not Started)*
- [ ] Integrate OTA logic into command system *(Not Started)*
- [ ] Test OTA update process *(Not Started)*

### For: Update Documentation & Onboarding

- [ ] Review and update `Project_Context.md`, onboarding guides *(In Progress)*
- [ ] Add missing documentation for new modules *(Not Started)*
- [ ] Standardize formatting across docs *(Not Started)*

---

## Copilot Workflow Guidance

### Mode Usage (Tandem Modes Recommended)

- **Reviewer-then-Sequential Thought:** Use to analyze goals, next steps, and file group mapping, then validate alignment and completeness.
- **Agent-then-Sequential Thought:** Apply edits, migrate entries, and reword for clarity and actionability, then validate phase alignment and clarity.
- **Reviewer-then-Agent:** Reviewer mode generates guidelines, Agent mode applies deep review and updates.
- **Reviewer-then-Branch:** Reviewer mode triages changes, Branch mode validates before merging, with Sequential Thought for final validation.
- **Diff-then-Agent:** Diff mode highlights differences, Agent mode resolves gaps interactively.
- **Auto-Fix-then-Sequential Thought:** Standardize formatting and entry style, then validate automation readiness.

### Recommended Workflow (Tandem Mode Checkpoints)

1. **Reviewer-then-Sequential Thought:** Summarize and extract all goals, next steps, and statuses, then validate mapping and alignment.
2. **Reviewer-then-Sequential Thought:** Map goals to file groups, then validate phase alignment.
3. **Agent-then-Sequential Thought:** Migrate, reword, and realign entries, maintaining formatting and statuses, then validate clarity and actionability.
4. **Auto-Fix-then-Sequential Thought:** Ensure formatting matches script requirements, then validate automation compatibility.
5. **Reviewer-then-Branch:** Validate changes and prepare for merge, with Sequential Thought for final review.
6. **Diff-then-Agent:** Compare new workflow to previous for completeness, then resolve any gaps.

### Checkpoints for Tandem Modes

- After initial Reviewer summary: Reviewer-then-Sequential Thought
- After mapping goals to file groups: Reviewer-then-Sequential Thought
- After next steps are aligned to goals: Agent-then-Sequential Thought
- After formatting fixes: Auto-Fix-then-Sequential Thought
- Before finalizing workflow for merge: Reviewer-then-Branch (with Sequential Thought)

---

## Notes

- Do not recalculate progress; preserve existing progress and legend sections.
- All goals and steps use checkbox entry style for automation compatibility.
- Existing statuses must be maintained throughout the entire final document using their legend entries.
- New goals/steps not previously listed are marked "Not Started".
- File group references are included for each goal.
- This workflow guidance is designed for Copilot automation and contributor onboarding.
