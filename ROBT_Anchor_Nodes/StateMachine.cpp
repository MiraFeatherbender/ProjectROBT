#include "StateMachine.h"
#include "CustomCommandFactory.h"
#include "CustomCommandClasses.h"
#include "ExternDefinitions.h"

static StateMachine* pStateMachine = nullptr;

StateMachine::StateMachine(OTAUpdater& otaUpdater)
  : otaUpdaterRef(otaUpdater),
    currentState(NODE_STATE_IDLE),
    atCommandBuffer(""),
    receivedCmdPayload(""),
    newCommand(false),
    commandName(""),
    params({})
    {
  pStateMachine = this;
}

void StateMachine::setReceivedCommand(uint8_t cmdType, const String& payload) {
  receivedCmdType = cmdType;
  receivedCmdPayload = payload;
  newCommand = true;
}

// The main update() state machine logic.
void StateMachine::update() {
  switch (currentState) {
    case NODE_STATE_IDLE:
      if (newCommand) {
        currentState = STATE_RECEIVED_CMD;
      }
      break;

    case STATE_RECEIVED_CMD:
      parseCommand();
      clearCommand();
      break;

    case STATE_CLASSIFY_CMD:
      // Parse the input into the command name and parameters
      classifyCmd();
      commandName = "";
      params.clear();
      break;

    case STATE_PROCESS_CUSTOM:
      Serial.println("Custom command executed successfully.");
      Serial.println(customReturn);
      customReturn.trim();
      customReturn.concat("\r\n");
      sendEspNowResponse(customReturn.c_str(), 1, 10);
      currentState = NODE_STATE_IDLE;
      break;

    case STATE_PROCESS_AT:
      processATCommand();                           // Forward the AT command.
      currentState = STATE_HANDLE_SENSOR_RESPONSE;  // Wait to process the response.
      break;

    case STATE_HANDLE_SENSOR_RESPONSE:
      {
        String response = receiveSensorResponse();  // Read the sensor response.
        if (response.length() > 0) {
          handleSensorResponse(response);  // Process and forward the response.
          currentState = NODE_STATE_IDLE;       // Return to idle after handling the response.
        }
        break;
      }

    case STATE_PROCESS_OTA:
      {
        Serial.println("Attempting to send OTA initiation message...");
        if (sendEspNowResponse("Initiating OTA update.\r\n", 1, 100)) {
          currentState = STATE_OTA_ACTIVATION;  // Proceed to the next state on success
        } else {
          Serial.println("Failed to send OTA initiation message after retries.");
          currentState = NODE_STATE_IDLE;  // Gracefully handle failure
        }
        break;
      }

    case STATE_OTA_ACTIVATION:
      Serial.println("Activating OTA update.");
      otaUpdaterRef.updateFirmware();
      currentState = NODE_STATE_IDLE;
      break;

    default:
      currentState = NODE_STATE_IDLE;
      break;
  }
}

void StateMachine::parseCommand() {
  if (receivedCmdType == CMD_OTA) {
    currentState = STATE_PROCESS_OTA;
  } else if (receivedCmdType == CMD_STANDARD) {
    atCommandBuffer = receivedCmdPayload;
    currentState = STATE_CLASSIFY_CMD;
  } else {
    Serial.print("Unknown command type: ");
    Serial.println(receivedCmdType, HEX);
    currentState = NODE_STATE_IDLE;
  }
}

void StateMachine::clearCommand() {
  receivedCmdPayload = "";
  newCommand = false;
}

// Determine if command is standard or custom.
void StateMachine::classifyCmd() {
  currentState = NODE_STATE_IDLE;
  if (atCommandBuffer.isEmpty()) {
    Serial.println("Empty input received. Ignoring...");
    return;  // Early return for empty input
  }
  if (!parseCmd(atCommandBuffer, commandName, params)) {
    Serial.println("Invalid input format. Ignoring...");
    return;  // Early return for invalid input
  }
  currentState = STATE_PROCESS_CUSTOM;

  // Fetch and execute the command
  if (!executeCommand(commandName, params, &customReturn)) {
    currentState = STATE_PROCESS_AT;  // If command doesn't exist, pass the input to the UWB sensor
  }
}

// Parse command and parameters from basic input.
bool StateMachine::parseCmd(const String& input, String& commandName, std::vector<String>& params) {
  // Find the space separating command name and parameters
  int spaceIndex = input.indexOf('=');
  commandName = (spaceIndex >= 0) ? input.substring(0, spaceIndex) : input;

  if (commandName.isEmpty()) { return false; }  // Return false if no command name is found
  if (spaceIndex < 0) { return true; }          // Command name exists, but no parameters to parse

  String paramString = input.substring(spaceIndex + 1);  // Parse parameters
  while (!paramString.isEmpty()) {
    int commaIndex = paramString.indexOf(',');

    if (commaIndex == -1) {
      params.push_back(paramString);
      return true;  // Successfully parsed command name and parameters
    }
    params.push_back(paramString.substring(0, commaIndex));  // Push the current parameter and update the remaining string
    paramString = paramString.substring(commaIndex + 1);     // Skip over ','
  }
}

// // Attempt to execute custom command with parameters.
// bool StateMachine::executeCommand(const String& commandName, const std::vector<String>& params) {
//   CustomCommand* command = commandFactory.getCommand(commandName);
//   if (!command) { return false; }  // Command not found

//   customReturn = command->execute(params);
//   return true;  // Command found and executed
// }

// Forward the AT command to the sensor.
void StateMachine::processATCommand() {
  if (atCommandBuffer.length() > 0) {
    // Serial.print("Forwarding AT command: ");
    // Serial.println(atCommandBuffer);
    Serial1.print(atCommandBuffer + "\r\n");
    atCommandBuffer = "";
  }
  return;
}

// Handles the given response: prints to Serial and sends via ESP-NOW.
void StateMachine::handleSensorResponse(const String& response) {
  Serial.println("Sensor response:");
  Serial.println(response);

  // Use sendEspNowResponse with retries built in.
  if (!sendEspNowResponse(response.c_str(), 1, 10)) {  // Retry up to 3 times
    Serial.println("Failed to send sensor response after retries.");
  }
}
