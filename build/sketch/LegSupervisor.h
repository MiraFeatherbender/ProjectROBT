#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\LegSupervisor.h"
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
   
    void clearTransitionQueue();  // Clear the transition queue (for dispatcher override)
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

    float getParkSteeringAngle() const { return parkSteeringAngle_; }
    void setParkSteeringAngle(float angle) { parkSteeringAngle_ = angle; }

    // Returns safe fade/slew time for a prescribed angle using ServoController's calculation
    uint32_t getSafeTiming(float prescribedAngle) const;

private:
    ServoController servo_;
    HallSensorHandler hallSensor_;
    ServoCalibration servoCal_;
    CommandPriority currentPriority_ = CommandPriority::PriorityNormal;
    SystemState currentState_ = SystemState::Booting;
    bool attachLEDC(const LEDCConfig& cfg);
    bool saveSweepSummary();
    std::vector<StateTransition> transitionQueue_;

    // Member variable for park angle only
    float parkSteeringAngle_;

    // Members for ProcessMoveCmd state machine
    bool moveCmdActive_ = false;
    unsigned long moveCmdStartTime_ = 0;
    float moveCmdSlewTime_ = 0.0f;
};

#endif //LEG_SUPERVISOR_H