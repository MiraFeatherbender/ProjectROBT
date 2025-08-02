#include <WiFi.h>
#include "ESPNowHandler.h"
#include "TrilaterationEngine.h"
#include "NodeManager.h"
#include "UWBNode.h"
#include "Mode.h"
#include "LCD_PinDefinitions.h"

// Global instance of ESPNowHandler.
ESPNowHandler espHandler;

// Global NodeManager instance.
NodeManager nodeManager(&espHandler);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (!espHandler.init()) {
    Serial.println("Error initializing ESP-NOW via ESPNowHandler");
    return;
  }

  // Set the external callback for ESP-NOW messages to NodeManager.
  espHandler.setMessageReceivedCallback([](const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len) {
    nodeManager.handleIncomingMessage(recv_info, data, data_len);
  });

  nodeManager.initializeNodes();

  TrilaterationEngine::getInstance().trilaterationStateMachine.buildAnchorMap();
  TrilaterationEngine::getInstance().startTask();


  analogWrite(LCD_BRIGHTNESS, 10);
}

void loop() {
  processSerialCommands();
  delay(10);
}

void processSerialCommands() {
  String command;

  uint8_t targetNode = 0;
  if (!nodeManager.processSerialInput(command, targetNode)) {
    return;
  }

  // // Check if the command is a mode-changing command using the modeMap.
  if (TrilaterationEngine::getInstance().setMode(command)) {
    return;
  }

  // Now, for non-mode changing commands, retrieve the current mode.
  Mode currentMode = TrilaterationEngine::getInstance().getMode();

  // Use switch-case to decide what to do based on the current mode.
  switch (currentMode) {
    case Mode::MANUAL:  // manual mode
      if (command.equalsIgnoreCase("ADVANCE")) {
        TrilaterationEngine::getInstance().advanceTask();  // notify task to advance
      } else {
        Serial.println("Command ignored in manual mode.");
      }
      break;
    case Mode::INACTIVE:  // inactive mode
      nodeManager.dispatchCommand(command, targetNode);
      break;
    default:
      Serial.println("Command ignored in free-running mode.");
      break;
  }
}
