# StealthChop2 Automatic Tuning Workflow (Experimental)

## Overview
This workflow outlines the process for automatic tuning of StealthChop2 (AT#1 and AT#2) for the TMC2160, based on extracted datasheet text.

---

## Workflow Steps

### 1. Power-Up & Initialization
- Ensure motor driver is powered and enabled.
- Motor is in standstill, powered with nominal run current (IRUN).
- If standstill reduction is enabled, issue a step pulse to switch drive to run current or set IHOLD = IRUN.
- Pin VS at operating level.

### 2. AT#1: Standstill Tuning
- Wait for standstill detection (>130ms at IRUN).
- StealthChop2 regulates to nominal current and stores result to PWM_OFS_AUTO.
- Driver may reduce chopper frequency during AT#1.
- Use reduced standstill current IHOLD < IRUN to avoid extended periods at lower chopper frequency.

### 3. AT#2: Motion/Homing Tuning
- Move motor at medium velocity (e.g., during homing).
- Target velocity: significant back EMF, full run current reached (typical range: 60–300 RPM).
- Monitor PWM_SCALE_SUM < 255, 1.5 * PWM_OFS_AUTO < PWM_SCALE_SUM < 4 * PWM_OFS_AUTO.
- StealthChop2 regulates to nominal current and optimizes PWM_GRAD_AUTO.
- Requires several hundred fullsteps for complete tuning.

### 4. Completion & Optimization
- Automatic tuning adapts settings during subsequent motion and standstill periods.
- Settings are further optimized for motor heating, supply variations, etc.
- Optionally, store PWM_GRAD_AUTO to CPU memory for faster future tuning.

### 5. Known Limitations & Recommendations
- Modifying GLOBALSCALER or VS voltage invalidates tuning; repeat AT#1/AT#2 if changed.
- Successful AT#1/AT#2 can be checked by monitoring PWM_SCALE_AUTO approaching zero during AT#2.
- For best results, use initial values for PWM_OFS and PWM_GRAD determined per motor type.
- Protect power stage and supply by tuning overcurrent protection.

---

## Decision Points & Hints
- If standstill reduction is enabled, ensure a step pulse is issued before AT#1.
- If AT#1 is not completed, AT#2 tuning will not start.
- If tuning fails, repeat the process or use stored initial parameters.

---

## End of Workflow

This workflow is generated from datasheet text only. Awaiting supplemental screenshots for further refinement.
