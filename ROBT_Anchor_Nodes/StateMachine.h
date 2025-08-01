#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>
#include "OTAUpdater.h"
#include "EspNowHandler.h"

// The possible states.
enum OuterNodeState {
  NODE_STATE_IDLE,
  STATE_RECEIVED_CMD,
  STATE_CLASSIFY_CMD,
  STATE_PROCESS_CUSTOM,
  STATE_PROCESS_AT, 
  STATE_HANDLE_SENSOR_RESPONSE,
  STATE_PROCESS_OTA,
  STATE_OTA_ACTIVATION
};

class StateMachine {
public:
  StateMachine(OTAUpdater& otaUpdater);

  // Called from your main loop.
  void update();

  // Called externally to deliver new command data.
  void setReceivedCommand(uint8_t cmdType, const String& payload);

private:
  // Current state.
  OuterNodeState currentState;

  // Buffer for AT commands.
  String atCommandBuffer;

  // Received command info.
  uint8_t receivedCmdType;
  String receivedCmdPayload;
  bool newCommand;

  // Command parsing variables.
  String commandName;
  std::vector<String> params;
  String customReturn;
  
  // Reference to the OTA updater.
  OTAUpdater& otaUpdaterRef;

  // Helper methods for modular actions.
  void processATCommand();                                                               // Forwards the AT command to the sensor.
  void handleSensorResponse(const String& response);                                     // Sends response via Serial & ESP-NOW.
  void parseCommand();                                                                   // Determines command type and updates state path.
  void clearCommand();                                                                   // Helper to clear command info.
  void classifyCmd();                                                                    // Determine if command is standard or custom.
  bool parseCmd(const String& input, String& commandName, std::vector<String>& params);  // Parse command and parameters from basic input.
  //bool executeCommand(const String& commandName, const std::vector<String>& params);     // Attempt to execute custom command with parameters.
};

#endif  // STATEMACHINE_H
