# TMC2160 Quick Configuration Workflows

## 1. Quick Configuration Guide (StealthChop)

### Current Setting

1. Check hardware setup and motor RMS current.
2. Set `GLOBALSCALER` as required to reach maximum motor current at `I_RUN = 31`.
3. Set `I_RUN` as desired (up to 31), `I_HOLD` to 70% of `I_RUN` or lower.
4. Set `I_HOLD_DELAY` to 1–15 for smooth standstill current decay.
5. Set `IHOLDDELAY` up to 255 for delayed standstill current reduction.
6. Configure chopper to test current settings.

### StealthChop Configuration

1. Set `en_pwm_mode` in `GCONF`.
2. In `PWMCONF`, set `pwm_autoscale` and `pwm_autograd`.
3. In `PWMCONF`, select `PWM_FREQ` with regard to `fCLK` for 20–40kHz PWM frequency.
4. In `CHOPCONF`, enable chopper using basic config (e.g., `TOFF=5`, `TBL=2`, `HSTART=4`, `HEND=0`).
5. Execute automatic tuning procedure AT.
6. Move the motor by slowly accelerating from 0 to `VMAX` operation velocity.
7. If performance is good up to `VMAX`, proceed to next step (SC2).
8. If not, select a velocity threshold for switching to spreadCycle chopper and set `TPWMTHRS`.

---

## 2. Tuning StealthChop and SpreadCycle

### StealthChop Tuning

1. Try motion above `TPWMTHRS`, if used.
2. If coil current overshoots upon deceleration:
   - In `PWMCONF`, decrease `PWM_LIM` (do not go below about 5).
3. Go to motor standstill and check motor current at `IHOLD_RUN`.
4. If standstill current is too high:
   - In `CHOPCONF`/`PWMCONF`, decrease `TBL` or PWM frequency and check impact on motor motion.
5. Optimize spreadCycle configuration if `TPWMTHRS` is used.

### SpreadCycle Configuration

1. Set `en_pwm_mode = 0` in `GCONF`.
2. In `CHOPCONF`, enable chopper using basic config (`TOFF=5`, `TBL=2`, `HSTART=0`, `HEND=0`).
3. Move the motor by slowly accelerating from 0 to `VMAX` operation velocity.
4. Monitor sine wave motor coil currents with current probe at low velocity.
5. If current zero crossing is smooth:
   - In `CHOPCONF`, increase `HEND` (max. 15).
6. Move motor very slowly or try at standstill.
7. If audible chopper noise:
   - In `CHOPCONF`, decrease `TOFF` (min. 2), try lower/higher `TBL`, or reduce motor current.
8. Move motor at medium velocity or up to max. velocity.
9. If audible chopper noise:
   - In `CHOPCONF`, decrease `HEND` and increase `HSTART` (max. 7).
10. Finished or enable coolStep.

---

## 3. Enabling coolStep (Only in Combination with SpreadCycle)

1. Enable coolStep.
2. Move the motor by slowly accelerating from 0 to `VMAX` operation velocity.
3. If coil current is sine-shaped at `VMAX`:
   - Decrease `VMAX`.
4. Set `THIGH` to match `TSTEP` at `VMAX` for upper coolStep velocity limit.
5. Monitor `SG_RESULT` value during medium velocity and check response with mechanical load.
6. If `SG_RESULT` goes down with load:
   - Increase `SGT`.
7. Set `TCOOLTHRS` slightly above `TSTEP` at the selected velocity for lower velocity limit.
8. In `COOLCONF`, enable coolStep basic config (`SEMIN=1`, all other 0).
9. Monitor `CS_ACTUAL` during motion in velocity range and check response with mechanical load.
10. If `CS_ACTUAL` does not reach `IRUN` with load before motor stall:
    - Increase `SEMIN` or choose narrower velocity limits.
11. Monitor `CS_ACTUAL` and motor torque during rapid mechanical load increment within application limits.
12. If `CS_ACTUAL` does not reach `IRUN` with load before motor stall:
    - Increase `SEUP`.
13. Finished.

---

## 4. Setting up dcStep

### Enable dcStep

1. In `CHOPCONF`, make sure `TOFF` is not less than 3. Use lowest good `TBL`. Set `WHIGH` and `WHIGHMIN`.
2. Set `VDCMIN` to about 5% to 20% of the desired operation velocity.
3. In `DCCTRL`, set `DC_TIME` depending on `TBL`:
   - `%100: TOFF=5, S5`
   - `%10: S7, %11: S5`
4. Start the motor at the targeted velocity `VMAX` and try to apply load.
5. If the motor reaches `VMAX` and has good torque:
   - Increase `DC_TIME`.
6. If the motor does not reach `VDCMIN` without step loss:
   - Decrease `DC_TIME` or increase `TOFF` or `VDCMIN`.
7. Finished or configure dcStep stall detection.

### Configure dcStep Stall Detection

1. In `DCCTRL`, set `DC_SG` to 1/16 the value of `DC_TIME`.
2. Set `TCOOLTHRS` to match `TSTEP` at a velocity slightly above `VDCMIN` for lower stallGuard velocity limit.
3. In `SW_MODE`, enable `sg_stop` to stop the motor upon stall detection.
4. Read out `RAMP_STAT` to clear `event_stop_sg` and restart the motor.
5. Accelerate the motor from 0 to `VMAX`.
6. If the motor stops during acceleration:
   - Slow down the motor to `VDCMIN` by applying load. Further increase load to stall the motor.
7. If the motor stops upon the first stall:
   - Finished.
8. If not:
   - Increase `DC_SG`.
