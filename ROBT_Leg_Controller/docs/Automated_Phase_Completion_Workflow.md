# Automated Phase Completion Workflow

This workflow coordinates your end-of-phase documentation review and updates. Each step is performed one at a time, with clear review points and instructions for your input. Copilot will make suggestions for updates, additions, or edits as appropriate for each step. If a patch fails, Copilot will present the attempted patch as a code block for easy copying and manual application.

---

## Step 1: Scan Documentation for TODOs and Outdated Sections

**Action:** Automatically search key docs (e.g., `Goals_And_Steps.md`, `Project_Context.md`, and other phase-relevant markdown files) for TODO, FIXME, or outdated comments.
**Review Point:** Copilot presents results for your review and suggests updates or edits as needed. You confirm if any flagged items need updates, and specify which files require changes.

## Step 2: Summarize Recent Changes

**Action:** List files/modules changed since last phase and summarize main updates.
**Review Point:** Copilot presents summary for your review, suggests additions or edits, and you can edit or expand the summary.

## Step 3: Review and Expand Goals and Steps (Goals_And_Steps.md)

### Step 3.1: Review Existing Entries

- **Action:** Systematically review all checklist entries in `Goals_And_Steps.md` for candidates to update their status (e.g., from incomplete to in progress, blocked, or complete).
- **Review Point:** Copilot presents a list of candidates for status changes, with reasoning. You confirm and approve updates.

### Step 3.2: Suggest New Entries

- **Action:** Based on recent workflow and project context, suggest new checklist entries for `Goals_And_Steps.md` that reflect work done or new priorities not yet listed as goals or steps.
- **Review Point:** Copilot presents suggested new entries for your approval or edits. You decide which to add to the checklist.

*Note: This step is specific to the review and expansion of `Goals_And_Steps.md` and ensures both status updates and new entries are handled distinctly before moving to subsequent workflow steps.*

## Step 4: Check Command Documentation

**Action:** Compare command reference with codebase for new/changed commands. If discrepancies are found (e.g., commands present in code but not docs, or obsolete commands in docs), Copilot suggests additions, removals, or archival.
**Review Point:** Copilot presents discrepancies and suggestions for your review and update. You confirm, edit, or archive command documentation as needed.

## Step 5: Run Progress Bar Update Script

**Action:** Trigger VS Code task/script to update progress bars in documentation.
**Review Point:** Copilot confirms completion and suggests corrections if needed. You verify progress bars are correct.

## Step 6: Generate Phase Completion Report

**Action:** Summarize updates, pending actions, and next steps. Save the phase completion report by overwriting the previous report file (e.g., `Phase_Completion_Report.md`) so it remains pinned and up-to-date for easy reference.

**Review Point:** Copilot presents the draft report for your review, suggests additions or edits, and you approve or edit the report. The final version is saved over the last report file.

---

**General Improvement:**  
At each review point, Copilot will explicitly prompt you for confirmation, edits, or additional input before proceeding to the next step. If automation fails, Copilot will present fallback code blocks for manual patching.

*To run this workflow: Ask Copilot to start the phase completion review. Copilot will guide you through each step, automating actions, making suggestions, and prompting for your input at each stage. If a patch fails, Copilot will present the attempted patch as a code block for easy copying.*
