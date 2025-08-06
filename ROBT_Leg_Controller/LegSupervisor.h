#ifndef LEG_SUPERVISOR_H
#define LEG_SUPERVISOR_H

#include "DriveConfig.h"
#include "ServoController.h"
#include "HallSensorHandler.h"
#include "ServoCalibration.h"
#include "FlashStorageTypes.h"
#include "SerialInputHandler.h"
#include "CommandParser.h"
#include "NVSManager.h"
#include "CommandInfo.h"

class LegSupervisor {
public:
    explicit LegSupervisor(const ServoConfig& ServoCFG);

    bool begin();  // Initializes the servo LEDC
    void queueTransitions(const std::vector<StateTransition>& transitions);
    void update(); // Processes state transitions and acts on hardware
    void captureInitialAngle(uint16_t raw_mv);  // Converts voltage to angle and injects it
    float getCurrentAngle() const;             // Returns current angle from servo
    void setSteeringAngle(float angle);
    void setRawSteeringAngle(float angle);
    void initADC(ADCConfig& cfg, void (*callback)());
    void handleParsedCommand(const ParsedCommand& cmd);
    CommandPriority getCurrentPriority() const { return currentPriority_; }
    SystemState getCurrentState() const { return currentState_; }
    
private:
    ServoController servo_;
    HallSensorHandler hallSensor_;
    ServoCalibration servoCal_;
    CommandPriority currentPriority_ = CommandPriority::NORMAL;
    SystemState currentState_ = SystemState::Booting;
    bool attachLEDC(const LEDCConfig& cfg);
    bool saveSweepSummary();
    std::vector<StateTransition> transitionQueue_;
};

#endif //LEG_SUPERVISOR_H