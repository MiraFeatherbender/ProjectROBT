# Copilot Modes Reference for Prompts & Workflows

This document summarizes all functional modes available for Copilot-driven prompts, workflows, and toolsets. Use these modes to tailor automation, review, and documentation processes for your project.

---

## 1. Reviewer Mode

- Quickly analyzes documentation and code for inconsistencies, outdated sections, and missing information.
- Generates a concise guideline or checklist for deeper review.
- Ideal for initial triage and planning.

## 2. Agent Mode

- Systematically reviews, updates, and aligns documentation using a checklist.
- Prompts for user confirmation, edits, or input before making changes.
- Ensures documentation matches current workflow, goals, and terminology.

## 3. Tandem Mode (Reviewer-then-Agent)

- Runs reviewer mode first to generate a guideline, then agent mode for deep, interactive review and update.
- Maximizes traceability, user control, and actionable outcomes.
- Recommended for thorough, section-by-section documentation consistency checks.

## 4. Diff Mode

- Compares documentation and code, highlighting differences and inconsistencies.
- Useful for syncing documentation with code changes or refactors.
- Can auto-generate update suggestions based on detected diffs.

## 5. Auto-Fix Mode

- Automatically applies safe, routine updates to documentation (e.g., formatting, minor corrections).
- Minimizes user intervention for low-risk changes.
- Best for large-scale, repetitive fixes.

## 6. Audit Mode

- Generates a summary report of documentation health, gaps, risks, and coverage.
- Useful for onboarding, management, or compliance reviews.
- Does not make changes—provides actionable insights.

## 7. Branch Mode

- Supports reviewing and updating documentation in feature branches before merging.
- Integrates with CI/CD workflows for pre-merge checks.
- Ensures documentation is up-to-date with new features or refactors.

---

### Usage Guidance

- Assign the mode that best fits your workflow or prompt goal.
- Modes can be combined (e.g., tandem + diff) for more robust processes.
- Each mode is modular and opt-in—use only what you need for your specific task.

---

_Reference this file when designing new prompts, workflows, or automation toolsets for ProjectROBT or similar projects._
