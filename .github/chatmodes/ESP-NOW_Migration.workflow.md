
# ESP-NOW Migration Chat Mode Workflow

## Step-by-Step Guidance

### 1. Module Research (Anchor Nodes)

**Mode:** Reviewer Mode
> Switch to Reviewer Mode for initial analysis and mapping of ESP-NOW modules.

- List all files/classes related to ESP-NOW (e.g., EspNowHandler.cpp/h, peer management, message dispatch).
- For each, explain its role and applicability to Leg Controller migration.

### 2. Leg Controller Integration Points

**Mode:** Reviewer Mode
> Continue in Reviewer Mode to analyze integration points and command routing.

- Review CommandParser.cpp/h and SerialInputHandler.cpp/h.
- Map how commands are received and routed.
- Note differences in broadcast/unicast handling between serial and ESP-NOW.

### 3. Migration Planning

**Mode:** Agent Mode
> Switch to Agent Mode for actionable migration planning and code adaptation.

- Suggest adaptation strategies for ESP-NOW modules.
- Recommend formatting and routing changes for broadcast/unicast commands.
- Ensure unified command handling via CommandParser.
- As migration planning progresses, offer to create new sub-planning workflow files for specific tasks (e.g., peer management, message formatting, integration testing) as needed. Always prompt the user for confirmation before creating a new workflow file, and document its purpose and scope clearly.

### 4. Actionable Review & Logging

**Mode:** Tandem Mode (Reviewer then Agent)
> Use Tandem Mode (Reviewer then Agent) for deep review and update cycles, maximizing traceability and actionable outcomes.

- For each module/integration point, provide reasoning and traceability.
- Log user experience issues, gaps, or manual interventions for future review.

### 5. Extensibility & Architectural Review (Future Phase)

**Mode:** Audit Mode (or Reviewer Mode for initial triage)
> Switch to Audit Mode for architectural health and extensibility review, or Reviewer Mode for initial triage.

- After migration, prompt for review of WiFi mode switching and unified communication manager design.

## References

- ESP-NOW_Command_OTA_Migration_Plan.md
- Wireless_Infrastructure.md
- Anchor Nodes and Leg Controller source files
