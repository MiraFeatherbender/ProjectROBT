#include "TrilaterationEngine.h"

TrilaterationEngine::TrilaterationEngine()
  : trilaterationStateMachine(snapshotQueue) {
  // Create the queue with space for 1 integer
  modeQueue = xQueueCreate(1, sizeof(Mode));
  if (modeQueue == NULL) {
    Serial.println("Failed to create mode queue");
  } else {
    Mode initialMode = Mode::INACTIVE;  // Default to inactive mode
    xQueueOverwrite(modeQueue, &initialMode);
  }
  // Dynamically create and assign the strategy
  IStateMachineStrategy* strategy = new DirectionFindingStrategy();  // Pick a strategy
  trilaterationStateMachine.setStateStrategy(strategy);              // Assign the strategy to the state machine
}

void TrilaterationEngine::startTask() {
  xTaskCreate(modeTaskFunction, "ModeTask", 2048, this, 2, &stateMachineHandle);
}

Mode TrilaterationEngine::getMode() const {
  Mode mode;
  if (xQueuePeek(modeQueue, &mode, 0) == pdPASS) {
    return mode;
  } else {
    Serial.println("Failed to peek mode queue");
    return Mode::INACTIVE;  // Return an invalid mode to indicate an error
  }
}

bool TrilaterationEngine::setMode(const String& command) {
  auto it = modeMap.find(command);  // Look up the command in the map
  if (it != modeMap.end()) {        // If it's a valid command
    Mode mode = it->second;         // Get the corresponding mode integer
    if (modeQueue != NULL) {
      xQueueOverwrite(modeQueue, &mode);
      Serial.printf("Mode updated to: %s (%d)\n", command.c_str(), mode);
      return true;  // Indicate success
    }
  }
  return false;  // Indicate failure
}

void TrilaterationEngine::advanceTask() {
  if (stateMachineHandle != NULL) {
    xTaskNotifyGive(stateMachineHandle);  // Notify the task to advance
  }
}

void TrilaterationEngine::modeTaskFunction(void* param) {
  TrilaterationEngine* self = static_cast<TrilaterationEngine*>(param);  // Access the instance
  while (true) {
    Mode currentMode = self->getMode();  // Use the getter to retrieve the mode

    switch (currentMode) {
      case Mode::FREERUN:    // Free-running mode
      case Mode::SINGLERUN:  // Single cycle mode
        self->trilaterationStateMachine.updateStateMachine();
        vTaskDelay(5 / portTICK_PERIOD_MS);
        break;

      case Mode::MANUAL:  // Manual mode
        // Wait for notification to advance
        if (ulTaskNotifyTake(pdTRUE, 100 / portTICK_PERIOD_MS) != 0) {
          self->trilaterationStateMachine.updateStateMachine();
        }
        break;

      case Mode::INACTIVE:  // Inactive mode
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        break;

      default:
        Serial.println("Unexpected mode encountered!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Keep the delay
        break;
    }
  }
}
