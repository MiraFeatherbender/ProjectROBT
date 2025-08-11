---
mode: agent
---
# Copilot Phase Completion Workflow Prompt

Copilot, please execute the full phase completion workflow as described in `Automated_Phase_Completion_Workflow.md`.

For each workflow step:

1. Announce the step number, its purpose, and the current Copilot mode (e.g., diff, audit, branch, reviewer, auto-fix).
2. Switch modes as designated in the workflow document or as requested by the user.
3. Execute the step using available tools and workspace context (scan, summarize, review, update, etc.).
4. Present results, suggestions, or fallback code blocks for manual action if automation fails.
5. Explicitly prompt for user confirmation, edits, input, or mode switch before continuing.
6. Repeat until all steps are complete and a final report is presented.

Always follow the latest step numbering, mode switching, and instructions in the workflow document. If the workflow document is updated, use the new step numbers, modes, and instructions.

Begin with "Step 1" in diff mode. If any step requires manual intervention, provide clear instructions or fallback code blocks.

----

**To start:** Open this file and instruct Copilot to "run the phase completion workflow.” You may request a mode switch at any review point.