# Copilot Instructions for ProjectROBT

These instructions guide GitHub Copilot's behavior and responses for this project. They reflect the project's coding style, collaboration goals, and documentation standards.

## Coding Style & Preferences

- Use modern C++ idioms and strong typing for all code except where Arduino syntax is required (main .ino file).
- Prefer modular, maintainable code with clear separation of hardware, configuration, and logic.
- Follow naming conventions: camelCase or snake_case for variables/functions, PascalCase for structs/classes, clear and scoped constants/enums.
- Maintain consistent indentation, spacing, and grouped/commented sections for clarity.
- Use inline comments for logic explanation and block comments for section/class/struct descriptions.
- Prefer switch/case statements over if statements where it improves readability and clarity.
- When if statements are needed, use zero nesting if possible and minimal nesting otherwise.

## Collaboration & Review

- Focus reviews on modularity, maintainability, and diagnostic/reporting capability.
- When reviewing documentation, check for onboarding clarity, technical completeness, and actionable troubleshooting tips.
- Summarize changes in documentation after major code edits or refactors.
- Prefer concise, actionable feedback and suggestions over lengthy explanations.
- When reviewing state machine or calibration logic, ensure edge cases and pipeline integration are addressed.
- When reviewing, always note if a change impacts other modules or requires updates elsewhere in the codebase or docs.
- Encourage use of branches for major features, refactors, or hardware integration.
- When suggesting code snippets, also check for necessary inclusions and suggest adding them if needed.

## Documentation & Onboarding

- Ensure documentation (README.md, Project_Context.md, Goals_And_Steps.md) is consistent, up-to-date, and cross-referenced.
- Highlight missing information, unclear instructions, or technical gaps for onboarding and future development.
- Suggest concrete edits or additions to improve onboarding experience and documentation quality.
- After major code changes, prompt for documentation updates in Project_Context.md and Goals_And_Steps.md.
- When onboarding or reviewing, ensure that new features and changes are reflected in the onboarding guide.

## Workflow

- Use prompt files for focused reviews, onboarding checks, and documentation consistency.
- Reference Project_Context.md for environment, hardware, and coding standards.
- Reference Goals_And_Steps.md for current priorities and next steps.

## Search and Reference Policy

- Ignore the `archive` folder when searching for or referencing active code, unless the archive is specifically requested for reference.

---

Copilot should periodically prompt to review and update this instructions file for relevance and applicability.
