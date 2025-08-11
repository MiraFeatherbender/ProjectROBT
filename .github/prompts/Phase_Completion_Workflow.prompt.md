---
mode: agent
---
# Copilot Phase Completion Workflow Prompt

Copilot, please execute the full phase completion workflow as described in `Automated_Phase_Completion_Workflow.md`.

For each workflow step:

1. Announce the step and its purpose.
2. Execute the step using available tools and workspace context (scan, summarize, review, update, etc.).
3. Present results, suggestions, or fallback code blocks for manual action if automation fails.
4. Explicitly prompt for user confirmation, edits, or input before continuing.
5. Repeat until all steps are complete and a final report is presented.

Begin with Step 1. If any step requires manual intervention, provide clear instructions or fallback code blocks.

---

**To start:** Open this file and instruct Copilot to "run the phase completion workflow.”