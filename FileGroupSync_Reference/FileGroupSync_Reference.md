# File Group Sync Reference

This document describes a universal, user-friendly configuration and workflow for synchronizing file groupings between markdown documentation and IDE Explorer views.

## Purpose

- Provide a single source of truth for project file groups.
- Enable easy, automated sync between markdown and virtual Explorer groups.
- Support user-defined styles and grouping logic.

---

## Example Config (`file-groups.json`)

```json
{
  "syncDesignator": "## **Project File Groups Sync**",
  "groups": [
    {
      "name": "Calibration Pipeline",
      "description": "Handles servo calibration and persistent storage.",
      "pattern": "ROBT_Leg_Controller/*Calibration*.*",
      "syncDesignator": "### **Calibration Pipeline Sync**"
    },
    {
      "name": "Command System",
      "description": "Command parsing and dispatch modules.",
      "pattern": "ROBT_Leg_Controller/Command*.*"
      // No syncDesignator: only included in full sync
    }
    // Add more groups as needed
  ],
  "instructions": "'name' is used for Explorer folder names. 'syncDesignator' (optional per group) is for markdown placement. Use glob patterns in 'pattern' for file grouping. The tool will expand patterns to actual file lists."
}
```

---

## Auto-Generated Markdown Output

---

## **Project File Groups Sync**

### Calibration Pipeline

Handles servo calibration and persistent storage.

Files:

- ROBT_Leg_Controller/ServoCalibration.cpp
- ROBT_Leg_Controller/ServoCalibration.h
- ROBT_Leg_Controller/FlashStorageTypes.h
- ROBT_Leg_Controller/NVSManager.cpp
- ROBT_Leg_Controller/NVSManager.h

### Command System

Command parsing and dispatch modules.

Files:

- ROBT_Leg_Controller/CommandFactory.cpp
- ROBT_Leg_Controller/CommandFactory.h
- ROBT_Leg_Controller/CommandParser.cpp
- ROBT_Leg_Controller/CommandParser.h

---

## Workflow

1. **Edit the config**: Add or update groups, descriptions, and patterns. Use `name` for Explorer folders, and `syncDesignator` for markdown sections (optional per group).
2. **Run sync tool/extension**: Automatically updates markdown and Explorer views. Explorer uses group names as folders; markdown uses syncDesignators for section placement.
3. **Customize style**: Change top-level or group-level `syncDesignator` to match your markdown preferences and modular documentation needs.
4. **Wildcard support**: Use glob patterns for scalable, minimal config. The tool expands patterns to file lists for both views.

---

## Benefits

- Minimal, readable config.
- User-driven style and grouping.
- Automation handles file expansion and updates.
- Consistent documentation and IDE organization.

---

## Tips

- Use clear group names and descriptions.
- Match `syncDesignator` to your documentation style. Only use it for markdown; Explorer view uses group names.
- Patterns can use wildcards for flexible grouping.
- Keep instructions up to date for contributors.

---

## For Extension Developers

- Parse config for both markdown and Explorer sync. Use `name` for Explorer folders, and `syncDesignator` for markdown sections.
- Expand wildcards to actual file lists.
- Allow user customization of styles and grouping logic. Document the distinction for clarity.

---

## Example Use Case

A robotics project with modular file groups can keep documentation and IDE views in sync, improving onboarding, troubleshooting, and workflow automation.

---

## Revision History

- v1.0 Initial reference document created (2025-08-12)
