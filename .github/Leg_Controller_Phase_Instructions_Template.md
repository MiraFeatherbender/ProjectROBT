# [Phase Name] Copilot Instructions

*For project-wide coding style, review, and documentation standards, see [Leg_Controller_copilot_instructions.md](./Leg_Controller_copilot_instructions.md).*

## Purpose

Guidance for developing, integrating, and reviewing the [Phase Name] in the Leg Controller project.

## Incremental Development and Testing

- Use test modules and serial print statements to validate logic and hardware interactions before implementing full methods.
- Prototype new features or routines with simple, traceable outputs to the serial console.
- Replace placeholders and test code with robust implementations as each stage is validated.
- Document test results and observations in code comments or project notes for future reference.

---

## [Phase Name] Completion Checklist

*Reference the group numbers in the Numbered Primary File References by Topic for each subheading below:*

### [Subphase/Feature 1] (Group X)

- [Checklist items for this subphase]

### [Subphase/Feature 2] (Group Y)

- [Checklist items for this subphase]

### [Subphase/Feature 3] (Group Z)

- [Checklist items for this subphase]

### Diagnostic/Reporting (Groups as needed)

- Add commands or routines to print summaries and diagnostics.
- Ensure reporting is clear and actionable for hardware alignment and troubleshooting.

### Testing (Groups as needed)

- Test full pipeline: [describe pipeline steps].
- Validate with hardware-in-the-loop and simulated data.

---

### Numbered Primary File References by Topic

#### 1. [Topic/Subsystem 1]

- [File1.cpp] / [File1.h] – [Description]
- [File2.h] – [Description]

#### 2. [Topic/Subsystem 2]

- [File3.cpp] / [File3.h] – [Description]
- [File4.ino] – [Description]

#### 3. [Topic/Subsystem 3]

- [File5.cpp] / [File5.h] – [Description]
- [File6.cpp] / [File6.h] – [Description]

#### 4. [Topic/Subsystem 4]

- [File7.cpp] / [File7.h] – [Description]

Reference these numbers in checklists or conversation (e.g., "Focus on group 1 for [feature] changes") for targeted analysis and automation.

---

## Copilot Agent Workflow for This Phase

- Always prioritize analysis, code tracing, and automation using the relevant numbered file group(s) based on checklist topic or user request.
- If a solution or review requires more context, expand outward from the primary group to related files, and document which groups are being referenced.
- Explicitly mention file group numbers in responses when suggesting changes, reviewing code, or troubleshooting, so the user knows the focus.
- When a checklist item is referenced, automatically map it to the corresponding file group(s) and explain the reasoning.
- After making changes or suggestions, prompt the user to review the relevant file group(s) for consistency and completeness.
- If the primary group does not resolve the issue, inform the user and expand the search to secondary or related groups as needed.
- Tailor automation, code generation, and review strategies to the current phase, using the file group system for targeted actions.

---

## Documentation

- Update onboarding and context docs to reflect [Phase Name] logic, storage, and retrieval process.
- Document commands, error codes, and troubleshooting steps.

---

You can copy this template and fill in the phase-specific details, checklist items, and file references for any new phase.
