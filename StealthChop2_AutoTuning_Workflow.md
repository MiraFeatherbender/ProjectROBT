# StealthChop2 Automatic Tuning — workflow (extracted from Figure 6.2)

This file is a concise text transcription of the automatic tuning flowchart shown in the attached datasheet images. It captures the decision steps, required conditions, and results so you can integrate the logic into code or docs.

## High-level phases

- AT#1  Stand still: tuning while motor is held still (stores PWM_OFS_AUTO)
- AT#2  Homing (or controlled motion): tuning while motor moves to optimize PWM_GRAD_AUTO
- Ready  Settings optimized and ongoing adaptation during operation

## Step-by-step flow

1. Power up
   - `PWM_GRAD_AUTO` becomes initialized on power up.

2. Is the driver enabled?
   - No: Wait/loop until the driver becomes enabled.

3. If the driver is enabled, check for standstill reduction:
   - If standstill reduction is enabled: issue (at least) a single step pulse and stop again so the motor is powered and currents run.
   - After the motor is powered, or if standstill reduction was not enabled, stealthChop2 regulates to nominal current and stores result to `PWM_OFS_AUTO`.
     - Requirement: the motor must stand still for >130 ms for AT#1 to complete.

4. Is `PWM_GRAD_AUTO` initialized from CPU? (diamond decision)
   - Yes: follow the branch that uses the CPU-provided `PWM_GRAD_AUTO` (skips AT#2 motion tuning step).
   - No: proceed to AT#2.

5. AT#2  Move the motor (example: homing)
   - Move with a constant, medium velocity ramp segment (controlled motion required).

6. While moving in AT#2
   - stealthChop2 regulates to nominal current and optimizes `PWM_GRAD_AUTO`.
   - Notes: requires roughly 8 fullsteps per change of 1; typically a few hundred fullsteps in sum are used to converge.

7. When optimization completes
   - `stealthChop2 settings are optimized`  system enters Ready state.
   - Option: store `PWM_GRAD_AUTO` to CPU memory via interface for a faster future tuning procedure.

8. Ongoing adaptation
   - stealthChop2 continues to tune during subsequent motion and standstill periods to adapt to motor heating, supply variations, etc.

## Important attention note (from figure)

- Modifying `GLOBALSCALER` or supply voltage `VS` invalidates the result of the automatic tuning process. Motor current regulation cannot compensate significant changes until the next AT#1 phase. Automatic tuning adapts to changed conditions whenever AT#1 and AT#2 conditions are fulfilled later in operation.

## Assumptions made while transcribing

- The attached images show the full flow for Figure 6.2 of the TMC2160 datasheet; I transcribed the visible decision labels and callouts.
- Minor layout or arrow-direction details (multi-branch loops) were interpreted to produce a linear, implementable procedure; if you want the literal drawn arrows preserved, I can export a rendered flowchart (Mermaid/Graphviz).

## Next steps I can take for you (pick one or I can do it now)

- Create a `Mermaid` flowchart version of this workflow and add it to this repo.
- Generate a small C/C++/Arduino pseudocode routine that implements the decision logic and stores/loads `PWM_GRAD_AUTO`/`PWM_OFS_AUTO`.
- Produce a PNG/SVG diagram (Mermaid -> SVG) and commit it to the repo.
- Nothing  you're good with this extracted text.

---

If you want one of the next steps, tell me which language or output format (Mermaid, Graphviz, Arduino sketch, etc.) and I will add it to the repo.
