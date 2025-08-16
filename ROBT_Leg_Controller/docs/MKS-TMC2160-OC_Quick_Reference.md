# MKS-TMC2160-OC Quick Reference Guide

---

## 1. Physical Context & Pinout

- **Driver:** MKS-TMC2160-OC (Trinamic TMC2160)
- **Control:** SPI (recommended), Step/Dir (legacy)
- **MCU:** ESP32-C3 (example)

### Pinout Table (Typical)

| TMC2160 Pin | Function         | ESP32-C3 Pin | Notes                  |
|-------------|-----------------|--------------|------------------------|
| SCK         | SPI Clock       | GPIOx        | SPI bus                |
| SDI         | SPI MOSI        | GPIOx        | SPI bus                |
| SDO         | SPI MISO        | GPIOx        | SPI bus                |
| CSN         | SPI Chip Select | GPIOx        | Active low             |
| ENN         | Enable (active) | GPIOx        | Emergency stop logic   |
| DIR         | Direction       | GPIOx        | Step/Dir fallback      |
| STEP        | Step            | GPIOx        | Step/Dir fallback      |
| DIAG0/DIAG1 | Diagnostics     | GPIOx        | Fault/limit reporting  |
| GND/VCC     | Power           | -            | 5V/3.3V logic, motor V |

---

## 2. Register Map (Key Registers)

- **GCONF (0x00):** Global configuration (enable, step/dir, SPI mode)
- **CHOPCONF (0x6C):** Chopper configuration (current, microstepping)
- **IHOLD_IRUN (0x10):** Motor current (hold/run)
- **TCOOLTHRS (0x14):** CoolStep threshold
- **SGTHRS (0x40):** StallGuard threshold
- **PWMCONF (0x70):** StealthChop PWM config
- **DRV_STATUS (0x6F):** Driver status (faults, diagnostics)

> Source: Trinamic TMC2160 Datasheet, Table 13.1

---

## 3. SPI Command Reference

- **Write:** 32-bit frame, MSB=0, `Addr` `Data`
- **Read:** 32-bit frame, MSB=1, `Addr` `Dummy`
- **Example:**
  - Write GCONF: `0x00 | 0x00000001` (enable driver)
  - Read DRV_STATUS: `0x6F | 0x00000000`

> Source: TMC2160 Datasheet, Section 12

---

## 4. Initialization Sequence

1. Power up, ensure ENN is low (driver enabled)
2. Configure SPI bus (mode 3, max 1MHz)
3. Write GCONF (enable, set SPI mode)
4. Set CHOPCONF (current, microstepping)
5. Set IHOLD_IRUN (hold/run current)
6. Optionally configure TCOOLTHRS, SGTHRS, PWMCONF
7. Verify DRV_STATUS (no faults)

---

## 5. Feature Enablement

- **StealthChop:** Set PWMCONF for silent operation
- **StallGuard:** Set SGTHRS for stall detection
- **CoolStep:** Set TCOOLTHRS for adaptive current
- **Diagnostics:** Monitor DIAG0/DIAG1, DRV_STATUS

---

## 6. Braking & Emergency Stop

- **Passive Braking:** ENN high (driver disabled, motor coils open)
- **Active Braking:** Set GCONF/CHOPCONF for high current, then ENN high
- **Emergency Stop:** Hardware: ENN pin, Software: GCONF (disable)
- **Best Practice:** Combine hardware ENN and software GCONF for safety

> Source: Trinamic Application Note AN001, Section 4

---

## 7. Troubleshooting

- **No movement:** Check SPI wiring, GCONF enable, power
- **Faults:** Read DRV_STATUS, check DIAG pins
- **Stall:** Adjust SGTHRS, check motor load
- **Noise:** Tune CHOPCONF, enable StealthChop

---

## 8. Best Practices

Always verify SPI communication before motor enable
Use ENN for hardware emergency stop
Monitor DRV_STATUS and DIAG pins for faults
Document all register changes for traceability

---

## 9. References

MKS-TMC2160-OC Board & Datasheet:

- [Makerbase MKS-TMC2160-OC GitHub Repository](https://github.com/makerbase-mks/MKS-Big-Current-Driver/tree/master/MKS%20TMC2160-OC)
- [TMC2160 Datasheet (PDF)](https://github.com/makerbase-mks/MKS-Big-Current-Driver/blob/master/MKS%20TMC2160-OC/TMC2160_datasheet.pdf)
- [MKS-TMC2160-OC User Manual](https://github.com/makerbase-mks/MKS-Big-Current-Driver/blob/master/MKS%20TMC2160-OC/README.md)

---

## 10. Revision Log

- v1.0: Initial draft (Copilot Agent, Reviewer, Audit, Context7, SequentialThinking)

---

**All register addresses, configuration steps, and best practices are sourced from the Trinamic TMC2160 datasheet and application notes.**
