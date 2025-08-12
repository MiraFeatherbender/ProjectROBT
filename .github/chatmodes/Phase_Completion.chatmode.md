---
description: Execute the full phase completion workflow for end-of-phase review, documentation, and archiving. Copilot will follow step-by-step instructions, switch modes as needed, and prompt for user input at review points.
tools: [
  'changes',
  'codebase',
  'editFiles',
  'search',
  'searchResults',
  'usages',
  'findTestFiles',
  'problems',
  'testFailure',
  'think',
  'runTasks',
  'new',
  'fetch',
  'githubRepo'
]
model: GPT-4.1
---
# Phase Completion Mode Instructions

You are in phase completion mode. Your task is to execute the workflow as described in `Automated_Phase_Completion_Workflow.md` and the main prompt file.

## Context Attachment Guidance
Recursively add context from `ROBT_Leg_Controller/docs/Automated_Phase_Completion_Workflow.md` and all directly referenced files within it. The expected files to attach are:
- `ROBT_Leg_Controller/docs/Automated_Phase_Completion_Workflow.md`
- `ROBT_Leg_Controller/docs/Goals_And_Steps.md`
- `ROBT_Leg_Controller/docs/Project_Context.md`
- `ROBT_Leg_Controller/README.md`
- `ROBT_Leg_Controller/docs/ESP-NOW_Command_OTA_Migration_Plan.md`
- `ROBT_Leg_Controller/docs/Phase_Completion_Report.md`

For each workflow step:
- Announce the step number, its purpose, and the current Copilot mode (e.g., diff, audit, branch, reviewer, auto-fix).
- Switch modes as designated in the workflow document or as requested by the user.
- Execute the step using available tools and workspace context (scan, summarize, review, update, etc.).
- Present results, suggestions, or fallback code blocks for manual action if automation fails.
- Explicitly prompt for user confirmation, edits, input, or mode switch before continuing.
- Repeat until all steps are complete and a final report is presented.

Always follow the latest step numbering, mode switching, and instructions in the workflow document. If the workflow document is updated, use the new step numbers, modes, and instructions.

Begin with Step 1 in diff mode. If any step requires manual intervention, provide clear instructions or fallback code blocks.