---
description: One-time migration of Goals_And_Steps.md to match the structure, guidance, and workflow of ROBT_Phase_Alignment.workflow.md.  Automatically cross-references codebase and documentation, supports tandem Copilot submodes, logs all changes and rationale, and prompts for user confirmation before major changes.
tools: ['codebase', 'think', 'search', 'editFiles', 'runTasks', 'searchResults']
model: GPT-4.1
---

# Goals Realignment Chat Mode Instructions

## Purpose
Migrate and realign Goals_And_Steps.md to the structure and intent of ROBT_Phase_Alignment.workflow.md, including new goals, file group references, and accomplishment markers. Preserve progress and legend sections. Map each workflow step to Copilot submodes for traceability.

## Workflow Steps & Submode Mapping

1. **Reviewer-then-Sequential Thought**
   - Summarize and extract all goals, next steps, and statuses from both files.
   - Validate mapping and alignment.
   - Log rationale and checkpoint.

2. **Reviewer-then-Sequential Thought**
   - Map goals to file groups as per workflow guidance.
   - Validate phase alignment.
   - Log rationale and checkpoint.

3. **Agent-then-Sequential Thought**
   - Migrate, reword, and realign entries in Goals_And_Steps.md.
   - Maintain formatting and statuses.
   - Validate clarity and actionability.
   - Log rationale and checkpoint.
   - Prompt user for confirmation before applying changes.

4. **Auto-Fix-then-Sequential Thought**
   - Standardize formatting and entry style for automation compatibility.
   - Validate automation readiness.
   - Log rationale and checkpoint.

5. **Reviewer-then-Branch (with Sequential Thought)**
   - Validate changes and prepare for merge.
   - Log rationale and checkpoint.
   - Prompt user for final confirmation.

6. **Diff-then-Agent**
   - Compare new workflow to previous for completeness.
   - Resolve any gaps interactively.
   - Log rationale and checkpoint.

## Automation & Confirmation

- Automatically cross-reference codebase and documentation for new or missing goals.
- Auto-generate checkpoints, notes, and accomplishment markers based on workflow file.
- Prompt for user confirmation before each major change.
- Log all changes, checkpoints, and rationale for traceability.
- Insert version/date frontmatter in migrated file.
- Use fallback code blocks (separated by section) if automation is incomplete.

## Notes

- Do not recalculate progress; preserve existing progress and legend sections.
- All goals and steps use checkbox entry style for automation compatibility.
- Existing statuses must be maintained throughout the entire final document using their legend entries.
- New goals/steps not previously listed are marked "Not Started".
- File group references are included for each goal.
- No onboarding steps unless required by the mode itself.

## Fallbacks

- If automation is incomplete, present fallback code blocks separated by section for any incontiguous file regions.
- Always prompt for user review and confirmation before finalizing.

# End of Goals Realignment Chat Mode Instructions
