# Automated Phase Completion Workflow

## Mode Switching Guidance

- At designated steps, Copilot may switch modes (e.g., diff, audit, branch, auto-fix, reviewer) to optimize analysis and automation.
- The current mode will be announced at the start of each step if a switch occurs.
- You may request a mode switch at any review point.

This workflow coordinates your end-of-phase documentation review and updates. Each step is performed one at a time, with clear review points and instructions for your input. Copilot will make suggestions for updates, additions, or edits as appropriate for each step. If a patch fails, Copilot will present the attempted patch as a code block for easy copying and manual application.

## Step 1: Prepare for Phase Completion

**Action:** Commit all uncommitted changes to the current branch. Run the diff against main and save results for reference.
**Mode:** Diff Mode (highlight changes and inconsistencies).
**Review Point:** Copilot presents the diff and confirms readiness to proceed. You may specify files or modules for deeper review. If automation fails, Copilot will present fallback code blocks for manual action.

## Step 2: Review File Changes Since Last Phase

**Action:** List all files and modules changed, newly added, archived, or removed since the previous phase completion. Summarize main updates and refactors. Use this change list to inform targeted review of documentation and checklists.  
**Mode:** Reviewer Mode (contextual analysis).  
**Review Point:** Copilot presents the change summary for your review and confirmation. You may specify files or modules for deeper review. If automation fails, Copilot will present fallback code blocks for manual action.

## Step 3: Audit Documentation Health (Optional)

**Action:** Generate a summary report of documentation health, gaps, and risks.  
**Mode:** Audit Mode (automated gap/risk detection).  
**Review Point:** Copilot presents the audit report for your review and prioritization.

## Step 4: Scan Documentation for TODOs, Outdated, or Stale Sections

**Action:** Compare changed files against documentation, goals, and steps. Flag any checklist items, goals, or project context sections that do not reflect recent changes, even if not explicitly marked as TODO/FIXME. Ensure the following documents are kept up to date:

- `Goals_And_Steps.md` (goals, next steps, and progress tracking)
- `Project_Context.md` (onboarding and project context)
- `README.md` (file overview, features, and usage)
- `ESP-NOW_Command_OTA_Migration_Plan.md` (migration, network hierarchy, and integration)

Update documentation file references, file group listings, and onboarding instructions to reflect new, archived, or changed files and milestone-based archiving. Present suggestions for updates, additions, or removals.

**Mode:** Audit Mode (automated flagging) + Reviewer Mode (validation/prioritization).  
**Review Point:** Copilot presents results for your review and suggests updates or edits as needed. You confirm if any flagged items need updates, and specify which files require changes. If automation fails, Copilot will present fallback code blocks for manual action.

## Step 5: Switch to Branch Mode

**Action:** All subsequent steps operate in branch mode, reviewing and updating documentation in the current feature/phase branch.  
**Mode:** Branch Mode (isolate changes to current phase/feature).  
**Review Point:** Copilot confirms mode switch and continues with branch-isolated review.

## Step 6: Review and Expand Goals and Steps (`Goals_And_Steps.md`)

### Step 6.1: Automated Status Review of Existing Entries

- **Action:**  
  - Use diff mode to analyze code and documentation changes since the last phase.
  - Automatically map changes to existing goals/steps, flagging candidates for status updates (e.g., “in progress”, “blocked”, “complete”).
  - Use reviewer mode to present flagged items with reasoning and context for user confirmation.
- **Process:**  
  1. Run diff mode to collect all relevant changes.
  2. Contextually associate changes with goals/steps.
  3. Present a list of candidates for status updates, with explanations.
  4. User reviews and approves updates.
- **Mode:** Diff Mode (context extraction) + Reviewer Mode (validation).
- **Review Point:** Copilot presents flagged goals/steps for status changes, with context and reasoning. You confirm, edit, or approve updates. If automation fails, Copilot will present fallback code blocks for manual action.

### Step 6.2: Automated Suggestion of New Goals and Next Steps

- **Action:**  
  - Use diff mode to surface new features, refactors, or fixes not yet reflected in goals/steps.
  - Use reviewer mode to synthesize context-derived goals and next steps, suggesting additions based on achievements, new modules, or discovered gaps.
  - Present suggestions for new checklist entries, mapping codebase actions to actionable goals/steps.
- **Process:**  
  1. Analyze diff results for new or changed functionality.
  2. Generate candidate goals/steps based on context and achievements.
  3. Present suggestions for new entries.
  4. User reviews, edits, and approves additions.
- **Mode:** Diff Mode (context extraction) + Reviewer Mode (synthesis/validation).
- **Review Point:** Copilot presents suggested new goals/steps for your approval or edits, with context and reasoning. You decide which to add to the checklist. If automation fails, Copilot will present fallback code blocks for manual action.

*Note: These enhancements ensure that both status updates and new entries are context-driven, actionable, and always reflect the true state of your codebase and project progress.*

## Step 7: Review and Update Project Context

**Action:** Ensure project context, onboarding, and environment documentation reflect the latest architecture, refactors, milestones, file group listings, onboarding instructions, and archive folder usage. Document milestone-based archiving and new documentation practices.  
**Mode:** Reviewer Mode (validation and synthesis).  
**Review Point:** Copilot presents suggested updates for your review and confirmation. If automation fails, Copilot will present fallback code blocks for manual action.

## Step 8: Check Command Documentation

**Action:** Compare command reference with codebase for new/changed commands. If discrepancies are found (e.g., commands present in code but not docs, or obsolete commands in docs), Copilot suggests additions, removals, or archival. Verify documentation of new error codes, query/set modes, and broadcast/payload handling for all commands.  
**Mode:** Reviewer Mode (cross-reference and validation).  
**Review Point:** Copilot presents discrepancies and suggestions for your review and update. You confirm, edit, or archive command documentation as needed. If automation fails, Copilot will present fallback code blocks for manual action.

## Step 9: Archive Previous Phase Completion Report

**Action:** Before generating a new phase completion report, Copilot must run the "Archive Phase Completion Report" VS Code task to copy the existing `Phase_Completion_Report.md` to the archive folder using the filename specified in the report body. Copilot must confirm the archive task completed successfully before proceeding. Confirm archived reports are referenced in onboarding/documentation.  
**Mode:** Reviewer Mode (validation and milestone/topic-based naming, with automated archival).  
**Review Point:** Copilot confirms the archive step is complete before proceeding to the next step. If automation fails, Copilot will present fallback code blocks for manual action.

## Step 10: Finalize Phase Title and Summary

**Action:** Review all changes, documentation, and decisions from Steps 1–10. Copilot must analyze the completed phase and suggest a concise, contextually appropriate archive filename for the new report. Copilot presents the filename to the user for confirmation or edits before generating the new report. The finalized title should be adapted for use as the archive file name in the next workflow, ensuring clear and consistent milestone/topic-based archiving. This ensures the completion report and its archive accurately reflect the scope and accomplishments of the phase.  
**Mode:** Reviewer Mode (final pass and collaborative phrasing).  
**Review Point:** Copilot presents candidate phase titles and summary phrasing for your review and edits. You confirm or refine the title and summary, and approve the archive file name format before proceeding.

## Step 11: Generate New Phase Completion Report Using Template

**Action:** Use the finalized phase title and summary, along with the structure, headers, and subheaders of the previous `Phase_Completion_Report.md`, to generate the new report. Populate the new report with updated content for the current phase, including a summary of changes to goals, steps, file structure, and documentation practices. Present the draft for your review and confirmation. Once confirmed, save the new report as `Phase_Completion_Report.md`, listing the agreed archive filename in the body.  
**Mode:** Reviewer Mode (report synthesis and validation).  
**Review Point:** Copilot presents the draft report for your review, suggests additions or edits, and you approve or edit the report. The final version is saved over the last report file. If automation fails, Copilot will present fallback code blocks for manual action.

---

**Final Reminder:** After completing the workflow, create a new branch for the next phase before making further changes.

**General Improvement:**  
At each review point, Copilot will explicitly prompt you for confirmation, edits, or additional input before proceeding to the next step. If automation fails, Copilot will present fallback code blocks for manual patching.

*To run this workflow: Ask Copilot to start the phase completion review. Copilot will guide you through each step, automating actions, making suggestions, and prompting for your input at each stage. If a patch fails, Copilot will present the attempted patch as a code block for easy copying.*
