# TMC2160 Usage Plan

This document outlines the minimal initialization steps and register settings required to activate the TMC2160 driver and prepare it for basic movement control.

---

## Minimal Initialization Steps

1. **GCONF (0x00):**  
   Set essential configuration bits:
   - `EN_PWM_MODE` (if using stealthChop, otherwise leave 0)
   - `SHAFT` (set direction as needed)
   - `RECALIBRATE_FIELD` (optional, for zero crossing recalibration)
   - Most other bits can be left at default for basic operation.

2. **IHOLD_IRUN (0x10):**  
   Set motor current:
   - `IHOLD_FIELD`: Standstill current (e.g., 8–16 for low power)
   - `IRUN_FIELD`: Run current (e.g., 16–31 for normal operation)
   - `IHOLDDELAY_FIELD`: Delay before power-down (e.g., 8)

3. **CHOPCONF (0x6C):**  
   Set microstepping and chopper mode:
   - `MRES_FIELD`: Microstep resolution (e.g., 0 for 256 microsteps, or lower for basic stepping)
   - `TOFF_FIELD`: Off time (must be >0 to enable driver, e.g., 3–5)
   - Other fields can be left at default for basic operation.

4. **DRV_CONF (0x0A):**  
   Set bridge timing and driver strength:
   - Use default values unless your MOSFETs require adjustment.

5. **TPOWERDOWN (0x11):**  
   Set delay after standstill before powering down (e.g., 10).

6. **GSTAT (0x01):**  
   Clear any reset or error flags by writing 1 to each bit.

---

## Example Initialization Sequence (Pseudocode)

```cpp
tmc2160_writeRegister(icID, TMC2160_GCONF, basicConfigValue);
tmc2160_writeRegister(icID, TMC2160_IHOLD_IRUN, (ihold << IHOLD_SHIFT) | (irun << IRUN_SHIFT) | (iholddelay << IHOLDDELAY_SHIFT));
tmc2160_writeRegister(icID, TMC2160_CHOPCONF, (mres << MRES_SHIFT) | (toff << TOFF_SHIFT));
tmc2160_writeRegister(icID, TMC2160_DRV_CONF, defaultDrvConfValue);
tmc2160_writeRegister(icID, TMC2160_TPOWERDOWN, tpowerdownValue);
tmc2160_writeRegister(icID, TMC2160_GSTAT, 0x07); // Clear all status flags
```

---

## Summary Table

| Register      | Field(s)         | Purpose                        | Example Value |
|---------------|------------------|--------------------------------|--------------|
| GCONF         | EN_PWM_MODE, SHAFT, RECALIBRATE | Basic config, direction, mode | 0x00000000   |
| IHOLD_IRUN    | IHOLD, IRUN, IHOLDDELAY         | Motor current settings        | 0x00101008   |
| CHOPCONF      | MRES, TOFF                    | Microstepping, driver enable  | 0x00000003   |
| DRV_CONF      | (default)                     | Bridge timing, driver strength| 0x00000000   |
| TPOWERDOWN    | TPOWERDOWN                    | Standstill power-down delay   | 0x0000000A   |
| GSTAT         | RESET, DRV_ERR, UV_CP         | Clear status flags            | 0x00000007   |

---

**In summary:**  
Set GCONF for basic mode, IHOLD_IRUN for current, CHOPCONF for microstepping and enable, DRV_CONF for bridge defaults, TPOWERDOWN for delay, and clear GSTAT. This will activate the driver and prepare it for basic movement commands. Adjust values as needed for your hardware and desired behavior.
