
# DM542T Full Digital Stepper Driver

Designed by StepperOnline® | Manufactured by Leadshine®

**Attention:** Please read this manual carefully before using the drive!

Contact: 7 Zhongke Road, Jiangning, Nanjing, China  
Tel: 0086-2587156578  
Website: [www.omc-stepperonline.com](https://www.omc-stepperonline.com)  
Email: <sales@stepperonline.com>

---

## Table of Contents

1. [Introductions, Features and Applications](#1-introductions-features-and-applications)
2. [Specifications](#2-specifications)
3. [Pin Assignment and Description](#3-pin-assignment-and-description)
4. [Control Signal Connector (P1) Interface](#4-control-signal-connector-p1-interface)
5. [Power Supply Selection](#5-power-supply-selection)
6. [Selecting Microstep Resolution and Drive Output Current](#6-selecting-microstep-resolution-and-drive-output-current)
7. [Wiring Notes](#7-wiring-notes)
8. [Typical Connection](#8-typical-connection)
9. [Sequence Chart of Control Signals](#9-sequence-chart-of-control-signals)
10. [Protection Functions](#10-protection-functions)
11. [Frequently Asked Questions](#11-frequently-asked-questions)

---

## 1. Introductions, Features and Applications

### Introduction

The DM542T is a fully digital stepper drive developed with advanced DSP control algorithms. It provides optimal torque, smooth motion, and nulls mid-range instability. Motor auto-identification and parameter auto-configuration allow quick setup for different motors. Compared to analog drives, DM542T offers lower noise, less heating, and smoother movement—ideal for high-requirement applications.

### Features

- Anti-Resonance for optimal torque and mid-range stability
- Motor auto-identification and auto-configuration at power-on
- Multi-Stepping: low resolution input produces higher microstep output
- 15 selectable microstep resolutions: 400, 800, 1600, 3200, 6400, 12800, 25600, 1000, 2000, 4000, 5000, 8000, 10000, 20000, 25000
- Soft-start (no “jump” at power-on)
- Input voltage: 20–50VDC
- 8 selectable peak currents: 1.00A, 1.46A, 1.91A, 2.37A, 2.84A, 3.31A, 3.76A, 4.20A
- Pulse input frequency up to 200 KHz (TTL compatible, optically isolated)
- Automatic idle-current reduction
- Suitable for 2-phase and 4-phase motors
- Supports PUL/DIR mode
- Over-voltage and over-current protection

### Applications

Compatible with stepper motors from NEMA17 to NEMA24. Used in X-Y tables, engraving machines, labeling machines, laser cutters, pick-and-place devices, and more—especially where low noise, low heating, high speed, and high precision are required.

## 2. Specifications

### Electrical Specifications (Tj = 25°C / 77°F)

| Parameter               | Min   | Typical | Max   | Unit   |
|-------------------------|-------|---------|-------|--------|
| Output Peak Current     | 1.0   | -       | 4.2   | A      |
| (3.0 RMS)               |       |         |       |        |
| Input Voltage           | +20   | +36     | +50   | VDC    |
| Logic Signal Current    | 7     | 10      | 16    | mA     |
| Pulse Input Frequency   | 0     | -       | 200   | kHz    |
| Pulse Width             | 2.5   | -       | -     | μs     |
| Isolation Resistance    | 500   | -       | -     | MΩ     |

### Operating Environment and Other Specifications

- Cooling: Natural or forced
- Environment: Avoid dust, oil fog, corrosive gases
- Ambient Temperature: 0°C – 65°C
- Operating Temperature: –10°C – 45°C
- Storage Temperature: –20°C – 65°C
- Humidity: 40%RH – 90%RH
- Vibration: 10–50Hz / 0.15mm
- Weight: Approx. 210g (7.4oz)

### Mechanical Specifications

Unit: mm [1 inch = 25.4mm]

    *Recommend side mounting for better heat dissipation*

#### Elimination of Heat

- Drive working temperature: <45°C (113°F)
- Motor working temperature: <80°C (176°F)
- Use automatic idle-current mode (current reduces to 50% when stopped)
- Mount drive vertically for best heat dissipation
- Use forced cooling if necessary

> Full Digital Stepper Drive DM542T
> Tel: 0086-2587156578 Web: <www.omc-stepperonline.com> Email:sales@stepperonline.com

Operating Environment and other Specifications

Cooling Operating Environment Storage Temperature Weight

Natural Cooling or Forced cooling

Environment Avoid dust, oil fog and corrosive gases

Ambient Temperature 0℃ － 65 ℃

Humidity 40%RH －90%RH

Operating Temperature －10 ℃ － 45 ℃

Vibration 10-50Hz / 0.15mm

-20 ℃ － 65 ℃

Approx. 210g (7.4oz)

Mechanical Specifications (unit: mm [1inch=25.4mm])

Figure 1: Mechanical specifications

*Recommend use side mounting for better heat dissipation Elimination of Heat

 Drive’s reliable working temperature should be <45 ℃(113 ℉ ), and motor working temperature should be <80 ℃(176 ℉);

 It is recommended to use automatic idle-current mode, namely current automatically reduce to 50% when motor stops, so as to reduce drive heating and motor heating;

 It is recommended to mount the drive vertically to maximize heat sink area. Use forced cooling method to cool the system if necessary. 3

> Full Digital Stepper Drive DM542T
> Tel: 0086-2587156578 Web: <www.omc-stepperonline.com> Email:sales@stepperonline.com

## 3. Pin Assignment and Description

DM542T has two connectors:

- **P1:** Control signals
- **P2:** Power and motor connections

### Connector P1 (Control Signals)

| Pin   | Function/Details |
|-------|------------------|
| PUL+  | Pulse signal (single pulse mode, rising edge active; 4–5V HIGH, 0–0.5V LOW; pulse width >2.5μs; use series resistors for +12V/+24V) |
| PUL–  | Ground for pulse signal |
| DIR+  | Direction signal (low/high voltage for motor direction; 4–5V HIGH, 0–0.5V LOW; swapping coil wires reverses direction) |
| DIR–  | Ground for direction signal |
| ENA+  | Enable signal (high level enables, low disables; usually left unconnected for enabled) |
| ENA–  | Ground for enable signal |

### Connector P2 (Power & Motor)

| Pin | Function/Details |
|-----|------------------|
| GND | Power ground |
| +V  | Power supply (20–50VDC, includes voltage fluctuation and EMF) |
| A+, A– | Motor Phase A |
| B+, B– | Motor Phase B |

## 4. Control Signal Connector (P1) Interface

DM542T accepts differential and single-ended inputs (open-collector and PNP output). Three optically isolated logic inputs on P1 minimize electrical noise. Line drive control signals are recommended for noisy environments.

**Connection Examples:**

- Open-collector (common-cathode)
- PNP signal (common-anode)

Refer to the manual diagrams for wiring details.

### Motor Connection Notes

#### 4-lead Motor

- Least flexible, easy to connect
- Speed–torque depends on winding inductance
- Set drive output current: multiply specified phase current by 1.4 for peak output current

#### 6-lead Motor

- Two configurations: high speed (half coil) or high torque (full coil)
- **Half coil:** Uses 50% of phase windings, lower inductance, more stable torque at high speed. Set drive output current: multiply per phase (unipolar) current by 1.4
- **Full coil:** Uses full windings, higher torque at low speed. Run at 70% of rated current to prevent overheating

#### 8-lead Motor

- Can be connected in series or parallel
- **Series:** Higher torque at low speed, more inductance, performance degrades at high speed. Run at 70% of rated current
- **Parallel:** More stable at high speed, lower torque at low speed, lower inductance. Set peak output current: multiply per phase (unipolar) current by 1.96, or bipolar current by 1.4

> Full Digital Stepper Drive DM542T
> Tel: 0086-2587156578 Web: <www.omc-stepperonline.com> Email:sales@stepperonline.com

## 5. Power Supply Selection

DM542T matches medium/small stepper motors (NEMA17–34). Supply voltage affects high-speed performance; output current affects torque at low speed.

### Power Supply Types

- Both regulated and unregulated supplies can be used
- Unregulated preferred (withstand current surge)
- If using regulated (switching) supply, ensure large current rating (e.g., 4A supply for 3A motor)
- Unregulated supply can be lower current than motor (typically 50–70% of motor current)
- Multiple drives can share one supply if capacity is sufficient; connect drives separately (not daisy-chained)

### Selecting Supply Voltage

- DM542T operates at +20–50VDC (including fluctuation and back EMF)
- Higher voltage = higher torque at high speed, but more noise/heating
- For reliability, use +20–45VDC to allow for fluctuation/back EMF

## 6. Selecting Microstep Resolution and Drive Output Current

DM542T uses an 8-bit DIP switch for microstep resolution and current settings.

### Microstep Resolution (SW5–SW8)

| Steps/rev (1.8° motor) | SW5 | SW6 | SW7 | SW8 |
|-----------------------|------|------|------|------|
| 400                   | OFF  | ON   | ON   | ON   |
| 800                   | ON   | OFF  | ON   | ON   |
| 1600                  | OFF  | OFF  | ON   | ON   |
| 3200                  | ON   | ON   | OFF  | ON   |
| 6400                  | OFF  | ON   | OFF  | ON   |
| 12800                 | ON   | OFF  | OFF  | ON   |
| 25600                 | OFF  | OFF  | OFF  | ON   |
| 1000                  | ON   | ON   | ON   | OFF  |
| 2000                  | OFF  | ON   | ON   | OFF  |
| 4000                  | ON   | OFF  | ON   | OFF  |
| 5000                  | OFF  | OFF  | ON   | OFF  |
| 8000                  | ON   | ON   | OFF  | OFF  |
| 10000                 | OFF  | ON   | OFF  | OFF  |
| 20000                 | ON   | OFF  | OFF  | OFF  |
| 25000                 | OFF  | OFF  | OFF  | OFF  |

### Dynamic Current Setting (SW1–SW3)

| Peak Current | RMS Current | SW1 | SW2 | SW3 |
|--------------|-------------|------|------|------|
| 1.00A        | 0.71A       | ON   | ON   | ON   |
| 1.46A        | 1.04A       | OFF  | ON   | ON   |
| 1.91A        | 1.36A       | ON   | OFF  | ON   |
| 2.37A        | 1.69A       | OFF  | OFF  | ON   |
| 2.84A        | 2.03A       | ON   | ON   | OFF  |
| 3.31A        | 2.36A       | OFF  | ON   | OFF  |
| 3.76A        | 2.69A       | ON   | OFF  | OFF  |
| 4.20A        | 3.00A       | OFF  | OFF  | OFF  |

*Note: Actual coil current may be less than dynamic setting at high speed due to motor inductance.*

### Standstill Current Setting (SW4)

- **OFF:** Standstill current = 50% of dynamic current
- **ON:** Standstill current = 100% of dynamic current
- Current automatically reduces to 50% after 0.4s of inactivity

### Motor Auto-Identification

At power-on, DM542T auto-identifies motor and configures parameters for optimal torque.

## 7. Wiring Notes

- Use twisted pair shielded cable for anti-interference
- Keep pulse/direction signal wires and motor wires separated by at least 10cm
- If sharing power supply, connect drives separately (not daisy-chained)
- Never pull/plug connector P2 while powered ON (risk of high back-EMF surge)

## 8. Typical Connection

A complete system includes: stepper motor, DM542T drive, power supply, and controller (pulse generator).

Refer to manual diagrams for typical wiring.

> Full Digital Stepper Drive DM542T
> Tel: 0086-2587156578 Web: <www.omc-stepperonline.com> Email:sales@stepperonline.com

## 9. Sequence Chart of Control Signals

To avoid faults, follow these timing rules:

- **t1:** ENA must be ahead of DIR by ≥5μs (ENA+ and ENA– usually not connected)
- **t2:** DIR must be ahead of PUL effective edge by ≥5μs
- **t3:** Pulse width ≥2.5μs
- **t4:** Low level width ≥2.5μs

## 10. Protection Functions

DM542T includes built-in protection features:

- **Over-current protection:** Activated when peak current exceeds limit (red LED blinks once)
- **Over-voltage protection:** Activated when voltage >60VDC (red LED blinks twice)
- When protection is active, motor shaft is free or LED blinks. Reset by repowering after resolving the issue.

## 10  

> Tel: 0086-2587156578 Web: <www.omc-stepperonline.com> Email:sales@stepperonline.com

## 11. Frequently Asked Questions

If the drive does not operate properly:

1. Identify if the problem is electrical or mechanical
2. Isolate system components and test independently
3. Document each troubleshooting step

### Common Symptoms and Possible Causes

| Symptom                          | Possible Cause |
|-----------------------------------|----------------|
| Motor not rotating                | No power, wrong microstep setting, wrong DIP switch current, fault condition, drive disabled |
| Motor rotates wrong direction     | Motor phases reversed, wrong DIP switch current, motor coil issue |
| Drive in fault                    | Fault condition exists |
| Erratic motor motion              | Weak/interfered control signal, wrong motor connection, motor coil issue |
| Motor stalls during acceleration  | Current setting too small, losing steps, motor undersized, acceleration too high, power supply voltage too low |
| Excessive motor/drive heating     | Inadequate cooling, automatic current reduction not used, current set too high |
