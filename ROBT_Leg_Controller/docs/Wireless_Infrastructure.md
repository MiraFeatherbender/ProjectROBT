# Wireless Infrastructure Design for ESP32 Modular Coordination

## Overview

This document outlines a unified wireless communication architecture for ESP32-based modular robotic systems. It enables seamless switching between ESP-NOW (peer-to-peer) and WiFi Station mode (TCP/IP), supporting robust coordination, debugging, and flexible deployment.

---

## Key Concepts

### 1. Dual-Mode Wireless Communication

- **ESP-NOW:** Peer-to-peer protocol using MAC addresses for direct device-to-device messaging. Ideal for low-latency, mesh-like coordination.
- **WiFi Station Mode:** Devices connect to a central WiFi network (e.g., router or hotspot). Enables TCP/IP communication for debugging, logging, and remote control.
- **Mode Switching:** Devices can switch between ESP-NOW and WiFi Station mode at runtime, triggered by command, button, or event.

### 2. Central Coordinator (Parent Device)

- Tracks MAC addresses of all child devices.
- Relays messages and manages communication mode for the network.
- Can act as a TCP/UDP server in WiFi mode, or as ESP-NOW master.

### 3. Modular Communication Manager

- Abstracts wireless protocol details.
- Maintains MAC address table and device registry.
- Handles runtime switching between ESP-NOW and WiFi.
- Synchronizes mode changes across all devices (e.g., via broadcast command).

### 4. Debugging Workflow

- Switch all devices to WiFi Station mode for remote debugging (GDB, logging, diagnostics) over TCP/IP.
- After debugging, revert to ESP-NOW for normal operation.
- Optionally, use a dedicated debug command or physical button to trigger mode switch.

---

## Implementation Notes

- **ESP-NOW and WiFi Station mode can run simultaneously** on ESP32-C3, but not with WiFi AP mode. Channel synchronization is required.
- **Performance trade-offs:** Throughput and reliability may be affected when both protocols are active.
- **Security:** Implement authentication for TCP/IP connections if exposed to public networks.
- **MAC Address Management:** Use MAC addresses for device identification and routing in both modes.
- **Modular Design:** Encapsulate communication logic in a manager class for easy maintenance and extension.

---

## Example Use Cases

- **Normal Operation:** ESP-NOW for fast, local coordination between robotic legs/modules.
- **Debugging/Diagnostics:** Switch to WiFi Station mode, connect to central server for remote debugging and data logging.
- **Flexible Deployment:** Adapt communication mode based on environment or operational needs.

---

## References

- ESP32 ESP-NOW documentation: <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html>
- ESP32 WiFi Station mode: <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html>
- ESP32 GDB remote debugging: <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/jtag-debugging/index.html>

---

## Next Steps

- Prototype modular communication manager class.
- Implement runtime mode switching and MAC address tracking.
- Test debugging workflow over TCP/IP.
- Document integration patterns and best practices.

---

*This document is a living design reference. Update as architecture evolves or new requirements emerge.*
