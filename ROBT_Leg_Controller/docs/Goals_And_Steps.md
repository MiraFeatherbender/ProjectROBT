
# Project Goals and Next Steps

**See also:** [Project Context Reference](./Project_Context.md)

---

## Task State Legend

- [ ] Not started
- [⏳] In progress
- [😰] In progress (stuck or stressful)
- [🧩] Blocked / Needs input
- [🚩] Needs attention / High priority
- [x] Complete

---

---


## Goals

- [ ] Integrate servo calibration triggers into custom AT command interface
- [ ] Integrate servo and stepper motion into custom AT command interface
    - [ ] Include target servo angle, target stepper velocity, transition time
- [ ] Add flash storage for calibration data, including center pulse time and backlash offset
    - [ ] Add "SweepProfile" struct to calibration for storage
- [ ] Ensure boot-time retrieval of calibration data from flash
- [ ] Replace static LEDC fade time calculation with parameterized slew time
- [⏳] Migrate ESP-NOW and OTAUpdater from anchor node codebase (serial command interface complete; see [migration plan](./ESP-NOW_Command_OTA_Migration_Plan.md))

---

## Next Steps

- [ ] Implement flash write and read routines for calibration data
    - [ ] NVS based. Use "SweepProfile"
- [x] Move "SweepProfile" to independent "FlashStorageTypes.h"
- [ ] Implement SweepProfile transfer flow:
    - [⏳] ServoCalibration creates SweepSummary
    - [⏳] LegSupervisor relays SweepSummary to NVSManager via getter
    - [⏳] NVSManager accepts SweepSummary from LegSupervisor to store in flash
- [x] Draft NVSManager.cpp
- [ ] Test boot-time retrieval of calibration data
- [ ] Prototype optional "calibrating" state in bootstate machine
- [⏳] Implement and test serial AT command input and parsing pipeline
