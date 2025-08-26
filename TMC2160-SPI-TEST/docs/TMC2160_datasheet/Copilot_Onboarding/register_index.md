# TMC2160 Register Index

## Group 1: Workflow-Critical Registers (Initial Setup & Basic Use)

These registers are prioritized for onboarding, initial configuration, and basic operation. They are referenced in most setup and tuning workflows.

| Register Name | Address | Function | Cross-References |
|--------------|---------|----------|------------------|
| `GCONF`      | 0x00    | Global configuration flags | Workflow setup, error handling |
| `IHOLD_IRUN` | 0x10    | Driver current control | Auto-tuning, velocity workflows |
| `TPOWERDOWN` | 0x11    | Delay after standstill | Linked to `IHOLD_IRUN`, stealthChop setup |
| `CHOPCONF`   | 0x6C    | Chopper configuration | Tuning, troubleshooting |
| `COOLCONF`   | 0x6D    | Smart energy/stallGuard config | Current scaling, error detection |
| `DRV_STATUS` | 0x6F    | Status flags, error reporting | Diagnostics, workflow steps |

---

## Group 2: Comprehensive Register List (Datasheet Reference)

This group lists all registers from the main datasheet tables, providing a complete technical reference for advanced troubleshooting, integration, and development. Registers are ordered by address and functional grouping

---

| Register Name | Address | Function | Cross-References |
|--------------|---------|----------|------------------|
| `GSTAT`      | 0x01    | Global status flags | Reset, error, undervoltage detection |
| `IOIN`       | 0x04    | Input pin state     | Pin monitoring, diagnostics |
| `OTP_PROG`   | 0x06    | OTP programming    | Factory settings, clock tuning |
| `FACTORY_CONF`| 0x08   | Factory configuration | Calibration, default setup |
| `SHORT_CONF` | 0x09    | Short circuit config| Protection, error handling |
| `DRV_CONF`   | 0x0A    | Driver configuration| Timing, overtemperature, gate strength |
| `GLOBAL_SCALER`| 0x0B  | Motor current scaling| Chopper hysteresis, motor adaptation |
| `OFFSET_READ`| 0x0C    | Offset calibration  | Phase A/B offset, calibration |
| `MSLUT[0-7]` | 0x60-0x67| Microstep table    | Sine wave generation, microstepping |
| `MSLUTSEL`   | 0x68    | LUT segmentation    | Microstep segment control |
| `MSLUTSTART` | 0x69    | LUT start values    | Initial microstep current |
| `MSCNT`      | 0x6A    | Microstep counter   | Position tracking |
| `MSCURACT`   | 0x6B    | Actual microstep current | Phase A/B current monitoring |
| `COOLCONF`   | 0x6D    | Smart energy/stallGuard config | Current scaling, error detection |
| `DCCTRL`     | 0x6E    | dcStep configuration| Commutation, stall detection |
| `PWMCONF`    | 0x70    | PWM mode config     | StealthChop, amplitude regulation |
| `PWM_SCALE`  | 0x71    | PWM scaling         | Amplitude monitoring |
| `PWM_AUTO`   | 0x72    | PWM auto tuning     | Amplitude auto-regulation |
| `LOST_STEPS` | 0x73    | Step loss counter   | dcStep, error tracking |
| `VDCMIN`     | 0x33    | dcStep minimum velocity | Sensorless commutation |

---

## Group 3: Detailed & Special Registers (Advanced, Troubleshooting, Cross-Linking)

Registers in this group are included for completeness, advanced troubleshooting, calibration, or because they are referenced in multiple workflows or datasheet breakdowns. Some may be repeated for cross-linking and clarity

---

| Register Name | Address | Function | Cross-References |
|--------------|---------|----------|------------------|
| `OTP_READ`   | 0x07    | OTP memory read         | Factory defaults, clock tuning |
| `FACTORY_CONF`| 0x08   | Factory configuration   | Calibration, default setup |
| `SHORT_CONF` | 0x09    | Short circuit config    | Protection, error handling |
| `DRV_CONF`   | 0x0A    | Driver configuration    | Timing, overtemperature, gate strength |
| `GLOBAL_SCALER`| 0x0B  | Motor current scaling   | Chopper hysteresis, motor adaptation |
| `OFFSET_READ`| 0x0C    | Offset calibration      | Phase A/B offset, calibration |
| `MSLUT[0-7]` | 0x60-0x67| Microstep table        | Sine wave generation, microstepping |
| `MSLUTSEL`   | 0x68    | LUT segmentation        | Microstep segment control |
| `MSLUTSTART` | 0x69    | LUT start values        | Initial microstep current |
| `MSCNT`      | 0x6A    | Microstep counter       | Position tracking |
| `MSCURACT`   | 0x6B    | Actual microstep current| Phase A/B current monitoring |
| `COOLCONF`   | 0x6D    | Smart energy/stallGuard config | Current scaling, error detection |
| `DCCTRL`     | 0x6E    | dcStep configuration    | Commutation, stall detection |
| `PWMCONF`    | 0x70    | PWM mode config         | StealthChop, amplitude regulation |
| `PWM_SCALE`  | 0x71    | PWM scaling             | Amplitude monitoring |
| `PWM_AUTO`   | 0x72    | PWM auto tuning         | Amplitude auto-regulation |
| `LOST_STEPS` | 0x73    | Step loss counter       | dcStep, error tracking |
| `VDCMIN`     | 0x33    | dcStep minimum velocity | Sensorless commutation |
| `CHOPCONF`   | 0x6C    | Chopper configuration   | Tuning, troubleshooting |
| `DRV_STATUS` | 0x6F    | Status flags, error reporting | Diagnostics, workflow steps |
| `GSTAT`      | 0x01    | Global status flags     | Reset, error, undervoltage detection |
| `IOIN`       | 0x04    | Input pin state         | Pin monitoring, diagnostics |
| `OTP_PROG`   | 0x06    | OTP programming         | Factory settings, clock tuning |

(Expand with all registers from the datasheet, cross-linking to workflows and technical chapters.)
