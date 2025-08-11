# ESP-NOW & OTA Migration Plan for Leg Controller

## 1. Network Architecture & Roles

- **Drive Coordinator (Parent):** Manages ESP-NOW network, acts as the central node for Leg Controllers.
- **Leg Controller (Child):** Modular firmware, accepts commands from any source (serial, ESP-NOW, future protocols) via unified command parsing.

## 2. Migration Steps

### 2.1. ESP-NOW Integration

#### a. ESP-NOW Module Adaptation

- Migrate/adapt `EspNowHandler.cpp/h` from Anchor Nodes.
- Refactor for Leg Controller’s modular architecture. Do not route ESP-NOW directly to the state machine.

#### b. Initialization

- Initialize ESP-NOW in `LegSupervisor`.
- Set up peer management: add Drive Coordinator as parent, optionally other Leg Controllers as peers.

#### c. Message Handling

- On ESP-NOW message receipt, `EspNowHandler` should construct a `CommandSourceContext` with `source = esp_now_` and broadcast/unicast info.
- Pass the received command and context directly to `CommandParser` for unified parsing and dispatch.
- `CommandParser` uses the context to differentiate source and handle broadcast/unicast payloads appropriately.

#### d. Testing

- Validate that commands received via ESP-NOW are parsed and dispatched identically to serial commands.
- Use diagnostic output to confirm source-agnostic command handling.

### 2.2. OTA Integration

#### a. OTA Module Adaptation

- Migrate/adapt `OTAUpdater.cpp/h` from Anchor Nodes.
- Integrate with `LegSupervisor` for event-driven updates.

#### b. Event Routing

- Route OTA events through `LegSupervisor`, not directly to the state machine.
- Ensure OTA status and errors are reported via diagnostics.

#### c. Testing

- Simulate OTA update events and validate firmware update flow.
- Confirm that OTA can be triggered and monitored via both serial and ESP-NOW commands.

## 3. Command System Integration

- Ensure `CommandFactory` and `CommandParser` are source-agnostic.
- All command sources (serial, ESP-NOW) should use the same parsing and dispatch pipeline.
- Update documentation to reflect unified command handling.

## 4. Hierarchical Plan Breakdown

1. **Prepare Leg Controller for ESP-NOW:**
   - Refactor `EspNowHandler` for modular integration.
   - Add Drive Coordinator as parent peer.

2. **Integrate ESP-NOW with Command Pipeline:**
   - Route ESP-NOW payloads to `CommandParser` for unified parsing.
   - Validate command execution from both sources.

3. **Integrate OTAUpdater:**
   - Refactor for event-driven updates via `LegSupervisor`.
   - Ensure OTA can be triggered by any command source.

4. **Testing & Validation:**
   - Test command handling and OTA updates from both serial and ESP-NOW.
   - Use diagnostics to confirm correct routing and execution.

5. **Documentation & Maintenance:**
   - Update migration plan and code comments to reflect new architecture.
   - Periodically review integration after major changes.
