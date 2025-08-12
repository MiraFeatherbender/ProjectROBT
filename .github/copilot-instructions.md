# Copilot Instructions for ProjectROBT

## Project Overview

- Modular C++ codebase for ESP32-based robotic leg control.
- Numbered file group system for targeted review, automation, and troubleshooting.
- All major modules, workflows, and documentation are organized for clarity and maintainability.

## File Group Reference System

- 1: Calibration Pipeline (ServoCalibration, FlashStorageTypes, NVSManager)
- 2: Command System (CommandFactory, CommandParser, CommandDispatcher, SerialInputHandler)
- 3: State Machine & Supervisor (LegSupervisor, ROBT_Leg_Controller.ino)
- 4: Persistent Storage (NVSManager, FlashStorageTypes)
- 5: Hardware Abstraction (DriveConfig, HallSensorHandler, ServoController, StepperController)
- 6: Documentation & Onboarding (docs/Project_Context.md, Goals_And_Steps.md, README.md, workflow files)
- 7: Archive & Reports (docs/archive/, milestone reports)
- Use these references for all automation, review, troubleshooting, and documentation updates.

## Search and Reference Policy

- Ignore the `archive` folder when searching for or referencing active code, unless the archive is specifically requested for reference.

## Coding Style & Preferences

- Modular C++ with strong typing, modern idioms, minimal nesting, early returns, guard clauses.
- Prefer switch/case for state management.
- Descriptive naming: camelCase/snake_case for variables/functions, PascalCase for structs/classes.
- Inline comments for logic, block comments for sections/classes.
- Custom hardware abstraction, minimal use of generic libraries.
- Consistent indentation, grouped/commented sections.
- Deterministic math, state machines, and hardware efficiency prioritized.
- Automated code formatting is preferred; always adhere to the consistent formatting patterns observed in the codebase. Fallback to codeblocks separated by sections for large or multi-file edits.

## Copilot Agent Workflow

- Use file group references for targeted actions and automation.
- Enable dynamic submode switching and creative tandem modes (see Copilot_Modes_Reference.md).
  - Examples of tandem modes:
    - Reviewer-then-Agent: Reviewer mode generates a guideline, Agent mode follows for deep review and update.
    - Agent-then-Auto-Fix: Agent mode applies edits, Auto-Fix mode standardizes formatting and corrects minor issues.
    - Reviewer-then-Diff: Reviewer mode analyzes for gaps, Diff mode highlights differences for validation.
    - Audit-then-Agent: Audit mode summarizes health/gaps, Agent mode addresses findings interactively.
    - Reviewer-then-Branch: Reviewer mode triages branch changes, Branch mode validates before merging.
    - Agent-then-Diff: Agent mode makes changes, Diff mode compares results for completeness.
    - Reviewer-then-Auto-Fix: Reviewer mode finds inconsistencies, Auto-Fix mode applies safe updates.
    - Diff-then-Agent: Diff mode highlights differences, Agent mode resolves them interactively.
  - Encourage combinations of modes (tandem) for enhanced review, troubleshooting, and documentation.
  - If a new mode combination is beneficial, offer it with explanation.
- Always refresh file context if manual changes are reported during edits, suggestions, or troubleshooting.
- Support dynamic review and troubleshooting patterns, encouraging creative, reasoned use of modes.
- Copilot should periodically prompt to review and update this instructions file for relevance and applicability.

## Documentation & Onboarding

- Reference Project_Context.md, Goals_And_Steps.md, and onboarding guides for environment setup, coding style, and workflow.
- Onboarding instructions are included as needed for Copilot’s own use; contributors should follow onboarding guides in docs.

## Troubleshooting & Review

- Use file group system for targeted troubleshooting.
- Summarize common error patterns and prevention checklist (see Project_Context.md).
- Encourage dynamic, creative review and troubleshooting using mode combinations.

## Mode Reference

- See Copilot_Modes_Reference.md for available modes.
- Assign, switch, and combine modes dynamically for best results.
- Use tandem modes creatively; see Copilot_Modes_Reference.md for recommended combinations and always explain rationale for new combinations.
