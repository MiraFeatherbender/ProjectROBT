# TMC2160 Math Formulas & Calculations

All relevant formulas for register configuration, timing, and driver setup, rendered in LaTeX.

## Microstep Time Reference

$$
TSTEP = \frac{1}{f_{STEP}} \text{ [units: s]}
$$

## TPOWERDOWN Delay

$$
\text{Delay} = \text{TPOWERDOWN} \times 2^{18} \times t_{CLK} \text{ [units: s]}
$$

## Off Time Calculation

$$
T_{OFF} = (12 + 32 \times \text{TOFF}) \times t_{CLK}
$$

## Passive Fast Decay Time

$$
N_{CLK} = 128 \times \text{TPFD}
$$

(Expand with additional formulas and calculation steps from all technical chapters.)

---

## Current Scaling (IRUN/IHOLD)

$$
I_{RUN} = \frac{V_{REF}}{R_{SENSE}} \times \frac{IRUN}{32}
$$

Where $V_{REF}$ is the reference voltage, $R_{SENSE}$ is the sense resistor value, and $IRUN$ is the register value (0–31).

## Velocity Thresholds

$$
v_{THRESH} = \frac{f_{CLK}}{T_{THRESH}}
$$

Where $T_{THRESH}$ is the threshold register value (e.g., TPWMTHRS, TCOOLTHRS, THIGH) and $f_{CLK}$ is the clock frequency.

## stallGuard2 Value

$$
SG_{RESULT} = \text{Measured mechanical load (0 = stall, higher = less load)}
$$

## PWM Amplitude Calculation

$$
PWM_{OFS} = \text{User-defined offset} \times \frac{CS_{ACTUAL}+1}{32}
$$

Where $CS_{ACTUAL}$ is the actual current scaling value.

---

(Expand with formulas for chopper timing, smart energy control, and advanced driver features as needed.)

---

## Advanced Formulas & Edge Cases

### GLOBAL_SCALER Current Adaptation

$$
I_{motor} = \frac{V_{sense}}{R_{sense}} \times GLOBAL\_SCALER \times IHOLD\_IRUN
$$

- $I_{motor}$: Motor current (A)
- $V_{sense}$: Sense voltage (V)
- $R_{sense}$: Sense resistor (Ω)
- $GLOBAL\_SCALER$: Register value
- $IHOLD\_IRUN$: Register value
- Source: TMC2160 datasheet, section 8.2

### External Clock Timing

$$
T_{sync} = \frac{1}{f_{ext}}
$$

- $T_{sync}$: Synchronization period (s)
- $f_{ext}$: External clock frequency (Hz)
- Source: TMC2160 datasheet, section 12.1

### Power Consumption

$$
P_{motor} = V_{motor} \times I_{motor}
$$

- $P_{motor}$: Power (W)
- $V_{motor}$: Motor voltage (V)
- $I_{motor}$: Motor current (A)
- Source: Standard electrical engineering reference

### Microstepping Accuracy

$$
 heta_{step} = \frac{360^\circ}{steps \times microsteps}
$$

- $\theta_{step}$: Step angle (degrees)
- $steps$: Motor steps per revolution
- $microsteps$: Microstep setting
- Source: TMC2160 datasheet, section 8.1

### stallGuard Sensitivity

$$
SG_{value} = COOLCONF_{sgt} \times scaling
$$

- $SG_{value}$: StallGuard threshold
- $COOLCONF_{sgt}$: Register value
- $scaling$: Device-specific factor
- Source: TMC2160 datasheet, section 10.3

### PWM Amplitude Regulation

$$
A_{pwm} = PWMCONF_{ampl} \times scaling
$$

- $A_{pwm}$: PWM amplitude
- $PWMCONF_{ampl}$: Register value
- $scaling$: Device-specific factor
- Source: TMC2160 datasheet, section 11.2

---

## Formula Cross-Links

- For register context, see [Register Index](register_index.md).
- For workflow application, see [Workflow Index](workflow_index.md).
- For troubleshooting, see [Troubleshooting Checklist](troubleshooting_checklist.md).
- For onboarding, see [Onboarding Guide](onboarding_guide.md).

---

**Expand with additional formulas, edge-case calculations, and technical notes as new features and workflows are added.**
