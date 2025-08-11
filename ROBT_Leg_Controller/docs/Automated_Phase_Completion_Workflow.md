# Automated Phase Completion Workflow

This workflow coordinates your end-of-phase documentation review and updates. Each step is performed one at a time, with clear review points and instructions for your input. Copilot will make suggestions for updates, additions, or edits as appropriate for each step. If a patch fails, Copilot will present the attempted patch as a code block for easy copying and manual application.

**Before starting:** Copilot will prompt you to commit any uncommitted changes to the current branch. Once all changes are committed, Copilot will run the diff against main so file changes can be referenced during review.

---

## Step 1: Review File Changes Since Last Phase

**Action:** List all files and modules changed, newly added, archived, or removed since the previous phase completion. Summarize main updates and refactors. Use this change list to inform targeted review of documentation and checklists.
**Review Point:** Copilot presents the change summary for your review and confirmation. You may specify files or modules for deeper review.

## Step 2: Scan Documentation for TODOs, Outdated, or Stale Sections

**Action:** Compare changed files against documentation, goals, and steps. Flag any checklist items, goals, or project context sections that do not reflect recent changes, even if not explicitly marked as TODO/FIXME. Ensure the following documents are kept up to date:

- `Goals_And_Steps.md` (goals, next steps, and progress tracking)
- `Project_Context.md` (onboarding and project context)
- `README.md` (file overview, features, and usage)
- Update documentation file references, file group listings, and onboarding instructions to reflect new, archived, or changed files and milestone-based archiving.
Present suggestions for updates, additions, or removals.

**Review Point:** Copilot presents results for your review and suggests updates or edits as needed. You confirm if any flagged items need updates, and specify which files require changes.

## Step 3: Review and Expand Goals and Steps (Goals_And_Steps.md)

### Step 3.1: Review Existing Entries

- **Action:** Systematically review all checklist entries in `Goals_And_Steps.md` for candidates to update their status (e.g., from incomplete to in progress, blocked, or complete).
- **Review Point:** Copilot presents a list of candidates for status changes, with reasoning. You confirm and approve updates.

### Step 3.2: Suggest New Entries

- **Action:** Based on recent workflow, expanded next steps, and project context, suggest new checklist entries for `Goals_And_Steps.md` that reflect work done or new priorities not yet listed as goals or steps. Map expanded next steps and goals from the phase completion report to checklist entries, flagging obsolete items for review (not removal).
- **Review Point:** Copilot presents suggested new entries for your approval or edits. You decide which to add to the checklist.

*Note: This step is specific to the review and expansion of `Goals_And_Steps.md` and ensures both status updates and new entries are handled distinctly before moving to subsequent workflow steps. Do not remove or archive obsolete items; this file is a historical record.*

## Step 4: Review and Update Project Context

**Action:** Ensure project context, onboarding, and environment documentation reflect the latest architecture, refactors, milestones, file group listings, onboarding instructions, and archive folder usage. Document milestone-based archiving and new documentation practices.
**Review Point:** Copilot presents suggested updates for your review and confirmation.

## Step 5: Check Command Documentation

**Action:** Compare command reference with codebase for new/changed commands. If discrepancies are found (e.g., commands present in code but not docs, or obsolete commands in docs), Copilot suggests additions, removals, or archival. Verify documentation of new error codes, query/set modes, and broadcast/payload handling for all commands.
**Review Point:** Copilot presents discrepancies and suggestions for your review and update. You confirm, edit, or archive command documentation as needed.

## Step 6: Run Progress Bar Update Script

**Action:** Trigger VS Code task/script to update progress bars in documentation.  
**Review Point:** Copilot confirms completion and suggests corrections if needed. You verify progress bars are correct.

## Step 7: Archive Previous Phase Completion Report

**Action:** Before generating a new phase completion report, copy the existing `Phase_Completion_Report.md` to the archive folder. Name the archived file to concisely reflect the topic or milestone of the completed phase (e.g., `Calibration_Pipeline_Completion_Report.md` for calibration pipeline completion, not by date). Confirm archived reports are named by milestone/topic and referenced in onboarding/documentation.
**Review Point:** Copilot confirms the archive step is complete before proceeding to the next step.

## Step 8: Generate New Phase Completion Report Using Template

**Action:** Use the structure, headers, and subheaders of the previous `Phase_Completion_Report.md` as a template for the new report. Populate the new report with updated content for the current phase, including a summary of changes to goals, steps, file structure, and documentation practices. Present the draft for your review and confirmation. Once confirmed, save the new report as `Phase_Completion_Report.md`.
**Review Point:** Copilot presents the draft report for your review, suggests additions or edits, and you approve or edit the report. The final version is saved over the last report file.

---

---

**Final Reminder:** After completing the workflow, create a new branch for the next phase before making further changes.

**General Improvement:**  
At each review point, Copilot will explicitly prompt you for confirmation, edits, or additional input before proceeding to the next step. If automation fails, Copilot will present fallback code blocks for manual patching.

*To run this workflow: Ask Copilot to start the phase completion review. Copilot will guide you through each step, automating actions, making suggestions, and prompting for your input at each stage. If a patch fails, Copilot will present the attempted patch as a code block for easy copying.*
