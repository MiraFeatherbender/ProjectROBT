<!-- markdownlint-disable MD033 -->
<!-- markdownlint-disable MD049 -->
# TMC2160 Register Field Reference

Below is a navigable reference for TMC2160 register fields, grouped by register. Expand each section to see the field macro names defined in the HAL.  

<details>
<summary><b>GCONF (0x00)</b></summary>
R/W: Read/Write | Bits: 32

- *TMC2160_RECALIBRATE_FIELD*:  
  1 = Zero crossing recalibration during driver disable (via `ENN` or via `TOFF` setting)  
  
- *TMC2160_FASTSTANDSTILL_FIELD*:  
  Timeout for step execution until standstill detection.  
  1 = Short time: 2^18 clocks  
  0 = Normal time: 2^20 clocks
  
- *TMC2160_EN_PWM_MODE_FIELD*:  
  1 = `stealthChop` voltage PWM mode enabled (depending on velocity thresholds).  
  Switch from off to on state while in stand-still and at `IHOLD = nominal IRUN` current, only.  
  
- *TMC2160_MULTISTEP_FILT_FIELD*:  
  1 = Enable step input filtering for `stealthChop` optimization with external step source (default = 1)
  
- *TMC2160_SHAFT_FIELD*:  
  1 = Inverse motor direction
  
- *TMC2160_DIAG0_ERROR__ONLY_WITH_SD_MODE_1__FIELD*:  
  1 = Enable `DIAG0` active on driver errors: Over temperature (`ot`), short to GND (`s2g`), undervoltage chargepump (`uv_cp`).  
  `DIAG0` always shows the reset-status, i.e. is active low during reset condition.  
  
- *TMC2160_DIAG0_OTPW__ONLY_WITH_SD_MODE_1__FIELD*:  
  1 = Enable `DIAG0` active on driver over temperature prewarning (`otpw`)
  
- *TMC2160_DIAG0_STALL_FIELD*:  
  1 = Enable `DIAG0` active on motor stall (set `TCOOLTHRS` before using this feature)
  
- *TMC2160_DIAG1_STALL_FIELD*:  
  1 = Enable `DIAG1` active on motor stall (set `TCOOLTHRS` before using this feature)
  
- *TMC2160_DIAG1_INDEX_FIELD*:  
  1 = Enable `DIAG1` active on index position (microstep look up table position `0`)
  
- *TMC2160_DIAG1_ONSTATE_FIELD*:  
  1 = Enable `DIAG1` active when `chopper` is on (for the coil which is in the second half of the `fullstep`)
  
- *TMC2160_DIAG1_STEPS_SKIPPED_FIELD*:  
  1 = Enable output toggle when steps are skipped in `dcStep` mode (increment of `LOST_STEPS`).  
  Do not enable in conjunction with other `DIAG1` options.  
  
- *TMC2160_DIAG0_INT_PUSHPULL_FIELD*:  
  0 = `DIAG0` is open collector output (active low)  
  1 = Enable `DIAG0` push pull output (active high)  
  
- *TMC2160_DIAG1_POSCOMP_PUSHPULL_FIELD*:  
  0 = `DIAG1` is open collector output (active low)  
  1 = Enable `DIAG1` push pull output (active high)  
  
- *TMC2160_SMALL_HYSTERESIS_FIELD*:  
  Modifies `TSTEP` threshold hysteresis from `1/16` to `1/32` for finer velocity thresholding.  
  Use for applications requiring reduced jitter sensitivity.  
  
- *TMC2160_STOP_ENABLE_FIELD*:  
  Enables stop-on-stall function when using internal motion controller.  
  1 = Stop motor on stall event, 0 = Ignore stall event for stopping.  
  
- *TMC2160_DIRECT_MODE_FIELD*:  
  Enables direct coil current mode.  
  1 = Bypass sequencer, use `XDIRECT` register for coil currents.  
  0 = Normal sequencer operation.  
  
- *TMC2160_TEST_MODE_FIELD*:  
  Reserved for factory test mode.  
  Should remain 0 during normal operation.  
 <!-- Add more field descriptions as you provide them -->
</details>

<details>
<summary><b>GSTAT (0x01)</b></summary>
R/W: Read/Write | Bits: 3

- *TMC2160_RESET_FIELD*:  
  1 = Indicates that the IC has been reset. All registers have been cleared to reset values.  
  
- *TMC2160_DRV_ERR_FIELD*:  
  1 = Indicates that the driver has been shut down due to overtemperature or short circuit detection.  
  Read `DRV_STATUS` for details.  
  The flag can only be cleared when the temperature is below the limit again.  
  
- *TMC2160_UV_CP_FIELD*:  
  1 = Indicates an undervoltage on the charge pump.  
  The driver is disabled during undervoltage.  
  This flag is latched for information.  

<blockquote>
<b>Note:</b> Re-write with '1' bit to clear respective flags.  
 </blockquote>
</details>

<details>
<summary><b>IOIN/OUTPUT (0x04)</b></summary>
R/W: Read | Bits: 8 (0–7) + 8 (24–31)

- *TMC2160_STEP_FIELD*:  
  `STEP` input pin
  
- *TMC2160_DIR_FIELD*:  
  `DIR` input pin
  
- *TMC2160_DCEN_CFG4_FIELD*:  
  `DCEN_CFG4` input pin
  
- *TMC2160_DCIN_CFG5_FIELD*:  
  `DCIN_CFG5` input pin
  
- *TMC2160_DRV_ENN_FIELD*:  
  `DRV_ENN` input pin
  
- *TMC2160_DCO_CFG6_FIELD*:  
  `DCO_CFG6` input pin
  
- *TMC2160_VERSION_FIELD*:  
  `VERSION`: 0x30 = first version of the IC
  
- *TMC2160_OUTPUT_PIN_POLARITY_FIELD*:  
  Identical numbers mean full digital compatibility.  

</details>

<details>
<summary><b>X_COMPARE (0x05)</b></summary>
R/W: Write | Bits: 20

- TMC2160_X_COMPARE_FIELD

</details>

<details>
<summary><b>OTP_PROG (0x06)</b></summary>
R/W: Write | Bits: 8

- TMC2160_OTPBIT_FIELD
- TMC2160_OTPBYTE_FIELD
- TMC2160_OTPMAGIC_FIELD

</details>

<details>
<summary><b>OTP_READ (0x07)</b></summary>
R/W: Read | Bits: 8

- TMC2160_OTP_TBL_FIELD
- TMC2160_OTP_BBM_FIELD
- TMC2160_OTP_S2_LEVEL_FIELD
- TMC2160_OTP_FCLKTRIM_FIELD

</details>

<details>
<summary><b>FACTORY_CONF (0x08)</b></summary>
R/W: Write | Bits: 5

- TMC2160_FCLKTRIM_FIELD

</details>

<details>
<summary><b>SHORT_CONF (0x09)</b></summary>
R/W: Write | Bits: 19

- TMC2160_S2VS_LEVEL_FIELD
- TMC2160_S2GND_LEVEL_FIELD
- TMC2160_SHORTFILTER_FIELD
- TMC2160_SHORTDELAY_FIELD

</details>

<details>
<summary><b>DRV_CONF (0x0A)</b></summary>
R/W: Write | Bits: 22

- *TMC2160_BBMTIME_FIELD*:  
  BBMTIME: Break-Before make delay  
  0=shortest (100ns) ... 16 (200ns) ... 24=longest (375ns)  
  >24 not recommended, use `BBMCLKS` instead  

  _Hint:_ Choose the lowest setting safely covering the switching event in order to avoid bridge cross-conduction.  
  Add roughly 30% of reserve.  
  _(Reset Default = 0)_
  
- *TMC2160_BBMCLKS_FIELD*:  
  BBMCLKS: Digital BBM time in clock cycles (typ. 83ns).  
  0..15: The longer setting rules (`BBMTIME vs. BBMCLKS`).  
  _(Reset Default: OTP 4 or 2)_
  
- *TMC2160_OTSELECT_FIELD*:  
  OTSELECT: Selection of over temperature level for bridge disable, switch on after cool down to 120°C / OTPW level.  
  00: 150°C  
  01: 143°C  
  10: 136°C (not recommended when VSA > 24V)  
  11: 120°C (not recommended, no hysteresis)  
  _Hint:_ Adapt overtemperature threshold as required to protect the MOSFETs or other components on the PCB.  
  _(Reset Default = %00)_
  
- *TMC2160_DRVSTRENGTH_FIELD*:  
  DRVSTRENGTH: Selection of gate driver current.  
  Adapts the gate driver current to the gate charge of the external MOSFETs.  
  00: weak  
  01: weak+TC (medium above OTPW level)  
  10: medium
  11: strong  
  _Hint:_ Choose the lowest setting giving slopes <100ns.  
  _(Reset Default = %10)_
  
- *TMC2160_FILT_ISENSE_FIELD*:  
  FILT_ISENSE: Filter time constant of sense amplifier to suppress ringing and coupling from second coil operation  
  00: low – 100ns  
  01: – 200ns  
  10: – 300ns  
  11: high – 400ns  
  _Hint:_ Increase setting if motor chopper noise occurs due to cross-coupling of both coils.  
  _(Reset Default = %00)_

</details>

<details>
<summary><b>GLOBAL_SCALER (0x0B)</b></summary>
R/W: Write | Bits: 8

- *TMC2160_GLOBAL_SCALER_FIELD*:  
  Global scaling of Motor current.  
  This value is multiplied to the current scaling in order to adapt a drive to a certain motor type.  
  This value should be chosen before tuning other settings, because it also influences chopper hysteresis.  
  0: Full Scale (or write 256)  
  1 ... 31: Not allowed for operation  
  32 ... 255: 32/256 ... 255/256 of maximum current.  
  _Hint:_ Values >128 recommended for best results.  
  _(Reset Default = 0)_

</details>

<details>
<summary><b>OFFSET_READ (0x0C)</b></summary>
R/W: Read | Bits: 16

- *TMC2160_OFFSET_READ_A_FIELD*:  
  Offset calibration result phase A (signed)
  
- *TMC2160_OFFSET_READ_B_FIELD*:  
  Offset calibration result phase B (signed)

</details>

<details>
<summary><b>IHOLD_IRUN (0x10)</b></summary>
R/W: Write | Bits: 5 (IHOLD) + 5 (IRUN) + 4 (IHOLDDELAY)

- *TMC2160_IHOLD_FIELD*:  
  Standstill current (0=1/32...31=32/32).  
  In combination with `stealthChop` mode, setting `IHOLD=0` allows to choose freewheeling or coil short circuit for motor stand still.  
  
- *TMC2160_IRUN_FIELD*:  
  Motor run current (0=1/32...31=32/32).  
  _Hint:_ Choose sense resistors in a way, that normal `IRUN` is 16 to 31 for best microstep performance.  
  
- *TMC2160_IHOLDDELAY_FIELD*:  
  Controls the number of clock cycles for motor power down after a motion as soon as `stst=1` and `TPOWERDOWN` has expired.  
  The smooth transition avoids a motor jerk upon power down.  
  0: instant power down  
  1..15: Delay per current reduction step in multiple of 2^18 clocks

</details>

<details>
<summary><b>TPOWERDOWN (0x11)</b></summary>
R/W: Write | Bits: 8

- *TMC2160_TPOWERDOWN_FIELD*:  
  Sets the delay time after stand still (`stst`) of the motor to motor current power down.  
  Time range is about 0 to 4 seconds.  
  *Attention:* A minimum setting of 2 is required to allow automatic tuning of `stealthChop` `PWM_OFFS_AUTO`.  
  _(Reset Default = 10)_  
  0...((2^8)-1) * 2^18 `t_CLK`

</details>

<details>
<summary><b>TSTEP (0x12)</b></summary>
R/W: Write | Bits: 20

- *TMC2160_TSTEP_FIELD*:  
  Actual measured time between two 1/256 microsteps derived from the step input frequency in units of 1/`fCLK`.  
  Measured value is (2^20)-1 in case of overflow or stand still.  
  All `TSTEP` related thresholds use a hysteresis of `1/16` of the compare value to compensate for jitter in the clock or the step frequency.  
  The flag `_small_hysteresis_` modifies the hysteresis to a smaller value of `1/32`.  
  (`Txxx*15/16`)-1 or (`Txxx*31/32`)-1 is used as a second compare value for each comparison value.  
  This means, that the lower switching velocity equals the calculated setting, but the upper switching velocity is higher as defined by the hysteresis setting.  
  In `dcStep` mode `TSTEP` will not show the mean velocity of the motor, but the velocities for each microstep, which may not be stable and thus does not represent the real motor velocity in case it runs slower than the target velocity.  

</details>

<details>
<summary><b>TPWMTHRS (0x13)</b></summary>
R/W: Write | Bits: 20

- *TMC2160_TPWMTHRS_FIELD*:  
  This is the upper velocity for `stealthChop` voltage PWM mode.  
  `TSTEP ≥ TPWMTHRS`  
  - `stealthChop` PWM mode is enabled, if configured  
  - `dcStep` is disabled

</details>

<details>
<summary><b>TCOOLTHRS (0x14)</b></summary>
R/W: Write | Bits: 20

- *TMC2160_TCOOLTHRS_FIELD*:  
  This is the lower threshold velocity for switching on smart energy `coolStep` and `stallGuard` feature (unsigned).  
  Set this parameter to disable coolStep at low speeds, where it cannot work reliably.  
  The stop on stall function (enable with sg_stop when using internal motion controller) and the stall output signal become enabled when exceeding this velocity.  
  In non-`dcStep` mode, it becomes disabled again once the velocity falls below this threshold.  
  `TCOOLTHRS` ≥ `TSTEP` ≥ `THIGH`:  
  - coolStep is enabled, if configured  
  - stealthChop voltage PWM mode is disabled  
  `TCOOLTHRS` ≥ `TSTEP`  
  - Stop on stall is enabled, if configured  
  - Stall output signal (`DIAG0/1`) is enabled, if configured

</details>

<details>
<summary><b>THIGH (0x15)</b></summary>
R/W: Write | Bits: 20

- *TMC2160_THIGH_FIELD*:  
  This velocity setting allows velocity dependent switching into a different chopper mode and fullstepping to maximize torque (unsigned).  
  The stall detection feature becomes switched off for 2-3 electrical periods whenever passing `THIGH` threshold to compensate for the effect of switching modes.  
  `TSTEP` ≤ `THIGH`:  
  - `coolStep` is disabled (motor runs with normal current scale)  
  - `stealthChop` voltage PWM mode is disabled  
  - If `vhighchm` is set, the chopper switches to `chm=1` with `TFD=0` (constant off time with slow decay, only).  
  - If `vhighfs` is set, the motor operates in fullstep mode and the stall detection becomes switched over to dcStep stall detection.  

</details>

<details>
<summary><b>XDIRECT (0x2D)</b></summary>
R/W: Read/Write | Bits: 9 (coil A current) + 9 (coil B current)

- *TMC2160_XDIRECT_FIELD*:  
  This register is used in direct coil current mode, only (`direct_mode = 1`).  
  It bypasses the internal sequencer. Specifies signed coil A current (bits 8..0) and coil B current (bits 24..16).  
  In this mode, the current is scaled by `IHOLD` setting.  
  Velocity based current regulation of `stealthChop` is not available in this mode.  
  The automatic `stealthChop` current regulation will work only for low stepper motor velocities.  
  2x -255...+255

</details>

<details>
<summary><b>VDCMIN (0x33)</b></summary>
R/W: Write | Bits: 23 (bits 0–22; only bits 22–8 used for value/comparison)

- *TMC2160_VDCMIN_FIELD*:  
  Automatic commutation dcStep minimum velocity. Enable dcStep by `DCEN` pin.  
  In this mode, the actual position is determined by the sensorless motor commutation and becomes fed back to the external motion controller.  
  In case the motor becomes heavily loaded, `VDCMIN` is used as the minimum step velocity.  
  _Hint:_ Also set `DCCTRL` parameters in order to operate dcStep.  
  (Only bits 22...8 are used for value and for comparison)

</details>

<details>
<summary><b>MSLUT__ (0x60)</b></summary>
R/W: Write | Bits: 32
<ul>
<!-- Add field macros and descriptions here -->
</ul>
</details>

<details>
<summary><b>MSLUTSEL (0x68)</b></summary>
R/W: Write | Bits: 32
<ul>
<!-- Add field macros and descriptions here -->
</ul>
</details>

<details>
<summary><b>MSLUTSTART (0x69)</b></summary>
R/W: Write | Bits: 8 + 8
<ul>
<!-- Add field macros and descriptions here -->
</ul>
</details>

<details>
<summary><b>MSCNT (0x6A)</b></summary>
R/W: Read | Bits: 10
<ul>
<!-- Add field macros and descriptions here -->
</ul>
</details>

<details>
<summary><b>MSCURACT (0x6B)</b></summary>
R/W: Read | Bits: 9 + 9
<ul>
<!-- Add field macros and descriptions here -->
</ul>
</details>

<details>
<summary><b>CHOPCONF (0x6C)</b></summary>
R/W: Read/Write | Bits: 32

- *TMC2160_DISS2VS_FIELD*:  
  Short to supply protection disable.  
  0: Short to VS protection is on, 1: Short to VS protection is disabled.  

- *TMC2160_DISS2G_FIELD*:  
  Short to GND protection disable.  
  0: Short to GND protection is on, 1: Short to GND protection is disabled.  

- *TMC2160_DEDGE_FIELD*:  
  Enable double edge step pulses.  
  1: Enable step impulse at each step edge to reduce step frequency requirement.  

- *TMC2160_INTPOL_FIELD*:  
  Interpolation to 256 microsteps.  
  1: The actual microstep resolution (MRES) becomes extrapolated to 256 microsteps for smoothest motor operation (useful for STEP/DIR operation only).  

- *TMC2160_MRES_FIELD*:  
  Microstep resolution. %0000: Native 256 microstep setting.  
  Normally use this setting with the internal motion controller.  
  %0001 ... %1000: 128, 64, 32, 16, 8, 4, 2, FULLSTEP.  
  Reduced microstep resolution esp. for STEP/DIR operation.  
  The resolution gives the number of microstep entries per sine quarter wave.  
  The driver automatically uses microstep positions which result in a symmetrical wave when choosing a lower microstep resolution.  
  step width=2*MRES [microsteps]  

- *TMC2160_TPFD_FIELD*:  
  Passive fast decay time.  
  TPFD allows dampening of motor mid-range resonances.  
  Passive fast decay time setting controls duration of the fast decay phase inserted after bridge polarity change.  
  Nclk=128*TPFD.  
  %0000: Disable, %0001 ... %1111: 1 ... 15.  

- *TMC2160_VHIGHCHM_FIELD*:  
  High velocity chopper mode.  
  This bit enables switching to chm=1 and fd=0, when `VHIGH` is exceeded.  
  This way, a higher velocity can be achieved. Can be combined with `vhighfs=1`.  
  If set, the TOFF setting automatically becomes doubled during high velocity operation in order to avoid doubling of the chopper frequency.  

- *TMC2160_VHIGHFS_FIELD*:  
  High velocity fullstep selection.  
  This bit enables switching to fullstep, when `VHIGH` is exceeded.  
  Switching takes place only at 45° position.  
  The fullstep target current uses the current value from the microstep table at the 45° position.  

- *TMC2160_TBL_FIELD*:  
  Blank time select. %00 ... %11:  
  Set comparator blank time to 16, 24, 36 or 54 clocks.  
  _Hint:_ %01 or %10 is recommended for most applications.  

- *TMC2160_CHM_FIELD*:  
  Chopper mode.  
  0 = Standard mode (spreadCycle),
  1 = Constant off time with fast decay time.  
  Fast decay time is also terminated when the negative nominal current is reached.  
  Fast decay is after on time.  

- *TMC2160_DISFDCC_FIELD*:  
  Fast decay mode.  
  chm=1: disfdcc=1 disables current comparator usage for termination of the fast decay cycle.  

- *TMC2160_TFD_FIELD*:  
  TFD: MSB of fast decay time setting TFD.  

- *TMC2160_HEND_FIELD*:  
  HEND: Hysteresis value.  
  %0000 ... %1111: Hysteresis is -3, -2, -1, 0, 1, ..., 12 (1/512 of this setting adds to current setting).  
  This is the hysteresis value which becomes used for the hysteresis chopper.  

- *TMC2160_OFFSET_FIELD*:  
  OFFSET: Sine wave offset.  
  %0000 ... %1111: Offset is -3, -2, -1, 0, 1, ..., 12.  
  This is the sine wave offset and 1/512 of the value becomes added to the absolute value of each sine wave entry.  

- *TMC2160_HSTRT_FIELD*:  
  HSTRT: Hysteresis start value added to HEND.  
  %000 ... %111: Add 1, 2, ..., 8 to hysteresis low value HEND (1/512 of this setting adds to current setting).  
  *Attention:* Effective HEND+HSTRT ≤ 16.  
  _Hint:_ Hysteresis decrement is done each 16 clocks.  

- *TMC2160_VSENSE_FIELD*:  
  *Bit 17 (Reserved):* Set to 0.  
  This bit is reserved in TMC2160 and must remain cleared for proper operation.  

- *TMC2160_TFD_FIELD*:  
  TFD [2..0]: Fast decay time setting.  
  chm=1: Fast decay time setting %0000 ... %1111:  
  Fast decay time setting TFD with Nclk=32*TFD (%0000: slow decay only).  

- *TMC2160_TOFF_FIELD*:  
  TOFF off time and driver enable.  
  Off time setting controls duration of slow decay phase Nclk=12 + 32*TOFF.  
  %0000: Driver disable, all bridges off.  
  %0001: 1 – use only with TBL ≥ 2.  
  =%0010 ... %1111: 2 ... 15.  

</details>
<details>
<summary><b>COOLCONF (0x6D)</b></summary>
R/W: Write | Bits: 25

- *TMC2160_SFILT_FIELD*:  
  `stallGuard2` filter enable.  
  0: Standard mode, high time resolution for `stallGuard2`.  
  1: Filtered mode, `stallGuard2` signal updated for each four fullsteps (resp. six fullsteps for 3 phase motor) only to compensate for motor pole tolerances.  
  
- *TMC2160_SGT_FIELD*:  
  `stallGuard2` threshold value.  
  This signed value controls `stallGuard2` level for stall output and sets the optimum measurement range for readout.  
  A lower value gives a higher sensitivity.  
  Zero is the starting value working with most motors.  
  -64 to +63: A higher value makes `stallGuard2` less sensitive and requires more torque to indicate a stall.  
  
- *TMC2160_SEIMIN_FIELD*:  
  minimum current for smart current control.  
  0: 1/2 of current setting (IRUN), 1: 1/4 of current setting (IRUN).  
  
- *TMC2160_SEDN_FIELD*:  
  current down step speed.  
  %00: For each 32 `stallGuard2` values decrease by one.  
  %01: For each 8 `stallGuard2` values decrease by one.  
  %10: For each 2 `stallGuard2` values decrease by one.  
  %11: For each `stallGuard2` value decrease by one.  
  
- *TMC2160_SEMAX_FIELD*:  
  `stallGuard2` hysteresis value for smart current control.  
  If the `stallGuard2` result is equal to or above (SEMIN+SEMAX+1)*32, the motor current becomes decreased to save energy.  
  %0000 ... %1111: 0 ... 15.  
  
- *TMC2160_SEUP_FIELD*:  
  current up step width.  
  Current increment steps per measured `stallGuard2` value.  
  %00 ... %11: 1, 2, 4, 8.  
  
- *TMC2160_SEMIN_FIELD*:  
  minimum stallGuard2 value for smart current control and smart current enable.  
  If the stallGuard2 result falls below SEMIN*32, the motor current becomes increased to reduce motor load angle.  
  %0000: smart current control coolStep off.  
  %0001 ... %1111: 1 ... 15.  

</details>

<details>
<summary><b>DCCTRL (0x6E)</b></summary>
R/W: Write | Bits: 24

- *TMC2160_DCCTRL_FIELD*:  
  dcStep (DC) automatic commutation configuration register (enable via pin `DCEN` or via VDCMIN):  
  bit 9...0: *DC_TIME*: Upper PWM on time limit for commutation (`DC_TIME` 1/fCLK).  
  Set slightly above effective blank time TBL.  
  bit 23...16: *DC_SG*: Max. PWM on time for step loss detection using dcStep `stallGuard2` in dcStep mode (`DC_SG`).  
  (`DC_SG` 16/fCLK)  
  Set slightly higher than `DC_TIME16`  
  0=disable  
  _Hint:_ Using a higher microstep resolution or interpolated operation, dcStep delivers a better `stallGuard2` signal.  
  `DC_SG` is also available above `VHIGH` if `vhighfs` is activated.  
  For best result also set `vhighchm`.  

</details>

<details>
<summary><b>DRV_STATUS (0x6F)</b></summary>
R/W: Read | Bits: 32

- *TMC2160_STST_FIELD*:  
   Standstill indicator.  
    This flag indicates motor stand still in each operation mode.  
    This occurs 2^20 clocks after the last step pulse.  
  
- *TMC2160_OLB_FIELD*:  
   Open load indicator phase B.  
    1: Open load detected on phase A or B.  
    _Hint:_ This is just an informative flag.  
    The driver takes no action upon it.  
    False detection may occur in fast motion and standstill.  
    Check during slow motion, only.  
  
- *TMC2160_OLA_FIELD*:  
   Open load indicator phase A.  
    1: Open load detected on phase A or B.  
    _Hint:_ This is just an informative flag.  
    The driver takes no action upon it.  
    False detection may occur in fast motion and standstill.  
    Check during slow motion, only.  
  
- *TMC2160_S2GB_FIELD*:  
   Short to ground indicator phase B.  
    1: Short to GND detected on phase A or B.  
    The driver becomes disabled.  
    The flags stay active, until the driver is disabled by software (TOFF=0) or by the ENN input.  
  
- *TMC2160_S2GA_FIELD*:  
   Short to ground indicator phase A.  
    1: Short to GND detected on phase A or B.  
    The driver becomes disabled.  
    The flags stay active, until the driver is disabled by software (TOFF=0) or by the ENN input.  
  
- *TMC2160_OTPW_FIELD*:  
   Overtemperature pre-warning flag.  
    1: Overtemperature pre-warning threshold is exceeded.  
    The overtemperature pre-warning flag is common for both bridges.  
  
- *TMC2160_OT_FIELD*:  
   Overtemperature flag.  
    1: Overtemperature limit has been reached.  
    Drivers become disabled until `otpw` is also cleared due to cooling down of the IC.  
    The overtemperature flag is common for both bridges.  
  
- *TMC2160_STALLGUARD_FIELD*:  
   `stallGuard2` status.  
    1: Motor stall detected (SG_RESULT=0) or dcStep stall in dcStep mode.  
  
- *TMC2160_CS_ACTUAL_FIELD*:  
   Actual motor current / smart energy current.  
  Actual current control scaling, for monitoring smart energy current scaling controlled via settings in register `COOLCONF`, or for monitoring the function of the automatic current scaling.  
  
- *TMC2160_FSACTIVE_FIELD*:  
   Full step active indicator.  
    1: Indicates that the driver has switched to fullstep as defined by chopper mode settings and velocity thresholds.  
  
- *TMC2160_STEALTH_FIELD*:  
   stealthChop indicator.  
    1: Driver operates in stealthChop mode.  
  
- *TMC2160_S2VSB_FIELD*:  
   Short to supply indicator phase B.  
    1: Short to supply detected on phase A or B.  
    The driver becomes disabled.  
    The flags stay active, until the driver is disabled by software (TOFF=0) or by the ENN input.  
    Sense resistor voltage drop is included in the measurement!
  
- *TMC2160_S2VSA_FIELD*:  
   Short to supply indicator phase A.  
    1: Short to supply detected on phase A or B.  
    The driver becomes disabled.  
    The flags stay active, until the driver is disabled by software (TOFF=0) or by the ENN input.  
    Sense resistor voltage drop is included in the measurement!
  
- *TMC2160_SG_RESULT_FIELD*:  
   `stallGuard2` result respectively PWM on time for coil A in standstill for motor temperature detection.  
    Mechanical load measurement: The `stallGuard2` result gives a means to measure mechanical motor load.  
    A higher value means lower mechanical load.  
    A value of 0 signals highest load.  
    With optimum SGT setting, this is an indicator for a motor stall.  
    The stall detection compares SG_RESULT to 0 in order to detect a stall.  
    SG_RESULT is used as a base for coolStep operation, by comparing it to a programmable upper and a lower limit.  
    It is not applicable in stealthChop mode.  
    `stallGuard2` works best with microstep operation or dcStep.  
    Temperature measurement: In standstill, no `stallGuard2` result can be obtained.  
    SG_RESULT shows the chopper on-time for motor coil A instead.  
    Move the motor to a determined microstep position at a certain current setting to get a rough estimation of motor temperature by a reading the chopper on-time.  
    As the motor heats up, its coil resistance rises, resulting in longer chopper on-time intervals.  

</details>

<details>
<summary><b>PWMCONF (0x70)</b></summary>
R/W: Write | Bits: 22

- *TMC2160_PWMCONF_FIELD*:  
  Voltage PWM mode chopper configuration.  
  _See separate table!_  
  _(Reset default=0xC40C001E)_

</details>

<details>
<summary><b>PWM_SCALE (0x71)</b></summary>
R/W: Read | Bits: 9 + 8

- *TMC2160_PWM_SCALE_SUM_FIELD*:  
   Actual PWM duty cycle.  
    This value is used for scaling the values CUR_A and CUR_B read from the sine wave table. (0...255)
  
- *TMC2160_PWM_SCALE_AUTO_FIELD*:  
   9 Bit signed offset added to the calculated PWM duty cycle.  
    This is the result of the automatic amplitude regulation based on current measurement. (signed -255...+255)

</details>

<details>
<summary><b>PWM_AUTO (0x72)</b></summary>
R/W: Read | Bits: 8 + 8

- *TMC2160_PWM_OFS_AUTO_FIELD*:  
  Automatically determined offset value (0...255)
  
- *TMC2160_PWM_GRAD_AUTO_FIELD*:  
  Automatically determined gradient value (0...255)

</details>

<details>
<summary><b>LOST_STEPS (0x73)</b></summary>
R/W: Read | Bits: 20

- *TMC2160_LOST_STEPS_FIELD*:  
  Number of input steps skipped due to higher load in dcStep operation, if step input does not stop when DC_OUT is low.  
  This counter wraps around after 2^20 steps. Counts up or down depending on direction. Only with SDMODE=1.  

</details>
