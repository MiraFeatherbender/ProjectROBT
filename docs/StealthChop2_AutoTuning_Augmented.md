# StealthChop2 Automatic Tuning — augmented & clarified (Figure 6.2 + chapter 6)

This document augments the earlier `StealthChop2_AutoTuning_Workflow.md` by incorporating details, formulas, success criteria and implementation tips drawn from chapter 6 of the TMC2160 datasheet (Figure 6.2 and surrounding text).

Source: TMC2160 datasheet (stealthChop, automatic tuning, PWM autoscale/grad/OFS sections).

## Purpose and scope

- Capture a practically actionable tuning procedure suitable for implementing in firmware or diagnostics.
- Include exact numeric conditions, safety notes, monitoring heuristics, and fallbacks from the datasheet.

## Summary of automatic tuning

- Two-phase automatic tuning (AT): AT#1 (standstill) then AT#2 (controlled motion/homing).
- The driver uses automatic current regulation (pwm_autoscale=1, pwm_autograd=1) to measure and adapt PWM_OFS_AUTO and PWM_GRAD_AUTO.
- AT must be performed with the motor and operating conditions matching the target application for best results.

## Key parameters and definitions

- PWM_OFS_AUTO: stored offset amplitude determined during AT#1 (standstill).
- PWM_GRAD_AUTO: gradient factor determined during AT#2 (motion).
- PWM_SCALE_SUM (read-only): actual PWM scaling value; approaching 0 during AT#2 motion indicates successful tuning.
- PWM_SCALE_AUTO: internal regulator that should regulate near 0 when tuned.
- GLOBALSCALER / VS: scaling and supply voltage; modifying either invalidates tuning results.
- IRUN / IHOLD: run/hold coil current settings used during tuning (IRUN required to be applied during AT#1).

## Required preconditions (border conditions)

AT#1 (PWM_OFS_AUTO)

- Motor in standstill.

- Actual current scale CS must equal run current IRUN (motor powered at nominal run current).

- Pin VS at operating level (stable supply voltage).

- If standstill reduction is enabled, a single initial step pulse must be issued so the driver returns to run current (or set IHOLD = IRUN for the sequence).

- Minimum duration: the standstill detection requires ≤130 ms (with internal clock) to store PWM_OFS_AUTO.

- Note: The driver may reduce chopper frequency during AT#1 if it cannot reach current; use reduced IHOLD < IRUN to avoid extended low-frequency periods.

AT#2 (PWM_GRAD_AUTO)

- Move the motor at a medium, constant velocity where significant back-EMF is generated and full run current can be reached.

- Recommended range: roughly 60–300 RPM (monitor and adjust for your motor).

- PWM_SCALE_SUM must remain < 255.

- Duration/step count: typically a few hundred fullsteps in sum; 8 fullsteps are required per change of 1 in PWM_GRAD_AUTO.

## Success criteria and monitoring

- AT#1 stores PWM_OFS_AUTO when stealthChop2 regulates to nominal current while the motor is powered and standing still >130 ms.
- AT#2 success: monitor `PWM_SCALE_AUTO` or `PWM_SCALE_SUM` during the constant velocity segment — `PWM_SCALE_AUTO` approaching 0 (or `PWM_SCALE_SUM` trending down toward nominal) indicates successful tuning.
- If `PWM_SCALE_SUM` reaches 255 it indicates the regulator cannot sustain full motor current (e.g., due to supply drop or too-high back-EMF).

## Known limitations and cautions

- Some drivers (e.g., TMC5161 noted in datasheet) cannot safely detect AT#1 completion; multiple motor start/stop events or the alternative approaches below may be necessary.
- Running stealthChop without correct tuning can produce high motor currents during deceleration ramps; verify with evaluation board and current probe.
- Modifying GLOBALSCALER or supply voltage VS invalidates the automatic tuning results. Re-run AT when these change.
- Lower current limit: there is a motor-specific lower current limit below which the current regulator cannot reliably measure/regulate. Ensure target IRUN exceeds this lower limit during AT#1.

## Useful formulas and examples from the datasheet

Lower current limit (thumb value):

```text
ILowerLimit = tBLANK * fPWM * (VM / RCOIL)
```

Example (from datasheet):

```text
RCOIL = 5 Ohm, VM = 24 V, TBL = %01 -> 24 tCLK, PWM_FREQ=%00 -> fPWM = 2/1024 tCLK
ILowerLimit = 24 * (2/1024) * (24/5) = 225 mA
```

Initial PWM_OFS estimate (velocity-based feed-forward mode):

```text
PWM_OFS ≈ (374 * RCOIL * ICOIL) / VM
```

First approximation for PWM_GRAD (from back-EMF):

```text
PWM_GRAD ≈ CBEMF * [V/rad/s factor] * (2π * fCLK * 1.46) / (VM * MSPR)
```

Where CBEMF is the motor back EMF constant, MSPR = microsteps per rotation, fCLK is the clock frequency. Use motor datasheet or measurement to estimate CBEMF.

## PWM_REG guidance

- PWM_REG is the proportional gain for the PWM_SCALE_AUTO regulator. Keep it as small as possible for stable behavior but large enough to react to target current changes.
- During AT#2, PWM_REG also needs to compensate for velocity changes; higher acceleration requires higher PWM_REG.
- A good starting value is PWM_REG = 1; tune by observing current response during acceleration (datasheet Figures 6.3–6.5 illustrate good/too-small examples).

## Implementation checklist (practical firmware steps)

1. Ensure stable VS and set run current IRUN to a value above the computed ILowerLimit.
2. Power up the driver and allow `PWM_GRAD_AUTO` to initialize (it becomes initialized on power-up).
3. Wait until driver enabled. If standstill reduction is enabled, issue one step pulse then stop to power motor to run current.
4. Perform AT#1:
   - Keep motor at standstill and powered at IRUN.
   - Wait at least 130 ms (or until `PWM_OFS_AUTO` registers a stable value). Read back `PWM_OFS_AUTO` if available.
   - If driver cannot reliably detect AT#1 completion, use Solution a) (slow-motion sequences) or Solution b) store initial parameters and skip AT#2.
5. Check if `PWM_GRAD_AUTO` was initialized from CPU memory:
   - If yes and an initial value exists, you may skip AT#2 and move to Ready (driver will keep adapting).
6. Otherwise perform AT#2:
   - Move the motor for homing or a controlled motion with a constant medium velocity.
   - Ensure enough steps: expect ~8 fullsteps per 1 change in gradient; collect a few 100 fullsteps in total for convergence.
   - Monitor `PWM_SCALE_AUTO` or `PWM_SCALE_SUM`: success is signaled by the regulator approaching 0 (PWM_SCALE_AUTO → 0) and PWM_SCALE_SUM reducing appropriately.
7. When tuning converges, optionally write `PWM_GRAD_AUTO` to CPU memory for faster future tuning.
8. Enter Ready state: stealthChop2 will continue background tuning during normal operation.

## Mitigations and fallback strategies

- Solution a) (improve detection in AT#1): Run a slow-motion pattern in AT#1 that includes small moves with a slow velocity (e.g., velocity 8 or lower / 6 Hz), performing at least 10 steps so the driver detects standstill between steps, completing AT#1 reliably.
- Solution b) (store initial parameters): Perform a full tuning on an evaluation rig and store `PWM_GRAD_AUTO` as an initial parameter on the CPU. Initialize the register on power up so AT#2 can be skipped in the field; driver will still refine over time.
- If PWM_SCALE_SUM saturates at 255, check supply voltage, GLOBALSCALER and motor connection; abort tuning and protect the power stage.

## Monitoring and diagnostics to add to firmware

- Read `PWM_SCALE_SUM` and `PWM_SCALE_AUTO` periodically during AT phases and report progress to the host.
- Expose flags for open load (OLA/OLB) and consider running a spreadCycle on-demand open-load test for safe diagnosis.
- Log `PWM_OFS_AUTO` and `PWM_GRAD_AUTO` after AT#1 and AT#2 respectively for troubleshooting and possible storage.

## Safety notes

- Ensure overcurrent protection and supply monitoring are tuned for your motor and load before running AT, especially when operating without the evaluation board.
- When switching between spreadCycle and stealthChop, use a low TPWMTHRS transfer velocity to avoid jerk and possible overcurrent.

---

File created from datasheet chapter 6. Use this as the authoritative implementation reference for stealthChop2 automatic tuning in the firmware.
