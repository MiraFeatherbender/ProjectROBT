#ifndef TRILATERATIONENGINE_H
#define TRILATERATIONENGINE_H

#include <Arduino.h>
#include <algorithm>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <map>
#include "Mode.h"
#include "NodeData.h"
#include "TrilaterationStateMachine.h"
#include "DirectionFindingStrategy.h"

class TrilaterationEngine {
private:

  QueueHandle_t modeQueue;                                                                               // Encapsulated queue
  TaskHandle_t stateMachineHandle;                                                                       // Handle for the FreeRTOS task
  QueueHandle_t snapshotQueue = xQueueCreate(3, sizeof(std::shared_ptr<std::map<uint8_t, NodeData>>*));  // Queue of map pointers

  TrilaterationEngine();

  // Strategy pointer
  IStateMachineStrategy* strategy = nullptr;
  
public:
  static TrilaterationEngine& getInstance() {
    static TrilaterationEngine instance;  // Single static instance
    return instance;
  }

  // Disable copy and assignment
  TrilaterationEngine(const TrilaterationEngine&) = delete;
  TrilaterationEngine& operator=(const TrilaterationEngine&) = delete;

  TrilaterationStateMachine trilaterationStateMachine;

  // Expose modeQueue
  QueueHandle_t getModeQueue() const {
    return modeQueue;
  }

  void startTask();                           // Method to create the FreeRTOS task
  Mode getMode() const;                       // Getter for the mode
  bool setMode(const String& mode);           // Setter for the mode
  void advanceTask();                         // Notify the task (xTaskNotify)
  static void modeTaskFunction(void* param);  // FreeRTOS task function
};

#endif  // TRILATERATIONENGINE_H
