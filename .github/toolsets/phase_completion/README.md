# Phase Completion Tool Set

This tool set streamlines the end-of-phase review, documentation, and archiving process for ProjectROBT. It bundles workflow prompts, automation tasks, and key documentation for a robust, traceable phase completion workflow.

## Included Components

- **Prompts**
  - `.github/prompts/Phase_Completion_Workflow.prompt.md` – Main workflow driver
  - `.github/prompts/documentation_consistency.prompt.md` – Documentation health checks
  - `.github/prompts/copilot_onboarding.prompt.md` – Onboarding guidance
  - `.github/prompts/project_context_review.prompt.md` – Project context review

- **Tasks**
  - `Diff Against Main` – Surfaces code/doc changes
  - `Archive Phase Completion Report` – Automates archiving using the filename in the report
  - `Build Firmware Bin (Active File)` – For hardware validation (if needed)
  - `Activate Copilot Instructions` – Ensures Copilot instructions are current

- **Docs**
  - `ROBT_Leg_Controller/docs/Automated_Phase_Completion_Workflow.md` – Workflow reference
  - `ROBT_Leg_Controller/docs/Phase_Completion_Report.md` – Current phase report
  - `ROBT_Leg_Controller/docs/Goals_And_Steps.md` – Checklist and next steps
  - `ROBT_Leg_Controller/docs/Project_Context.md` – Onboarding and context
  - `ROBT_Leg_Controller/docs/Copilot_Modes_Reference.md` – Copilot modes guide

## How to Use

1. **Start the workflow:**  
   Open `Phase_Completion_Workflow.prompt.md` and instruct Copilot to run the workflow.
2. **Run the diff task:**  
   Use `Diff Against Main` to review changes.
3. **Review and update docs:**  
   Use the documentation consistency and context review prompts to ensure all docs are up-to-date.
4. **Update goals and steps:**  
   Edit `Goals_And_Steps.md` as part of the workflow.
5. **Generate and review the phase report:**  
   Update `Phase_Completion_Report.md` as needed.
6. **Archive the report:**  
   Run the `Archive Phase Completion Report` task to automate archiving.
7. **Onboard or update Copilot instructions:**  
   Use onboarding prompt/task as needed.

## Best Practices

- Run the workflow in a clean branch and commit all changes before archiving.
- Use reviewer mode for validation and synthesis; supplement with audit mode for automated checks.
- Reference the Copilot modes guide for optimal mode selection.
- Document any manual interventions in the phase report.

## Workspace Configuration Guidance

You do **not** need to move your docs folder.  
A VS Code workspace configuration (`.code-workspace` file) can simply reference all relevant folders and files in their current locations.  
You can also use VS Code’s “Multi-root Workspaces” to group prompts, tasks, and docs for easy access, while keeping your existing structure.
