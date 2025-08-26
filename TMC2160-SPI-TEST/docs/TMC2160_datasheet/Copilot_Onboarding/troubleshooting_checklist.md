# TMC2160 Troubleshooting Checklist

A modular checklist for error flags, configuration issues, and workflow validation.


---

## Error Flag Checklist

- Check `DRV_STATUS` for:
	- `otpw`, `ot` (overtemperature)
	- `stallGuard` (stall detection)
	- `s2ga`, `s2gb` (short to ground)
	- `olb`, `ola` (open load)

## Configuration Validation

- Verify `CHOPCONF` settings for:
	- Microstep resolution (`MRES`)
	- Decay (`TOFF`, `TPFD`)
	- Hysteresis (`HEND`, `HSTRT`)
- Ensure `IHOLD_IRUN` and `TPOWERDOWN` are set within recommended ranges.
- Cross-reference workflow steps with register values.

## Calibration & Tuning Issues

- For calibration issues:
	- Re-run offset calibration workflow
	- Check `OFFSET_READ` values
- For PWM amplitude problems:
	- Retune `PWMCONF`
	- Verify `PWM_SCALE` feedback

## Advanced Diagnostics

- For short circuit errors (`s2ga`, `s2gb`):
	- Verify MOSFETs and sense resistors
	- Inspect PCB layout and connections
- For open load detection (`olb`, `ola`):
	- Check wiring and phase connections
- For overtemperature flags (`otpw`, `ot`):
	- Reduce current
	- Improve cooling and airflow
- If stallGuard is unreliable:
	- Adjust `COOLCONF` sensitivity
	- Check mechanical load and motor condition

## Onboarding Notes

- Each troubleshooting step is cross-linked to relevant workflows and register documentation.
- For detailed procedures, see [Workflow Index](workflow_index.md).
- For register details, see [Register Index](register_index.md).
- For math-based validation, see [Math Formulas](math_formulas.md).

---

**This checklist supports modular troubleshooting, onboarding, and advanced diagnostics for the TMC2160. Expand with additional error patterns and workflow links as needed.**
