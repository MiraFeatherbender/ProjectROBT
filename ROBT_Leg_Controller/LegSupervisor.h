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
    // Initialization & Setup
    explicit LegSupervisor(const ServoConfig& ServoCFG);
    bool begin();  // Initializes the servo LEDC
    void initADC(ADCConfig& cfg, void (*callback)());
    void captureInitialAngle(uint16_t raw_mv);  // Converts voltage to angle and injects it
    void handleSweepEventFromISR(const SweepEvent& event);

    // State Machine & Transitions
    void update(); // Processes state transitions and acts on hardware
    void queueTransitions(const std::vector<StateTransition>& transitions);
    void clearTransitionQueue();  // Clear the transition queue (for dispatcher override)

    // Servo Control
    float getCurrentAngle() const;             // Returns current angle from servo
    void setSteeringAngle(float angle);
    void setRawSteeringAngle(float angle);
    uint32_t getSafeTiming(float prescribedAngle) const; // Returns safe fade/slew time for a prescribed angle
    uint32_t getServoPulseUS() const { return servo_.getPulseUS(); }
    void startCalibration() { servoCal_.begin(); }


    // Command Handling
    void handleParsedCommand(const ParsedCommand& cmd);
    void setContext(const CommandSourceContext& ctx) { context_ = ctx; }

    // State & Priority Accessors
    CommandPriority getCurrentPriority() const { return currentPriority_; }
    SystemState getCurrentState() const { return currentState_; }
    StateMachine getCalibrationState() const { return servoCal_.getState(); }

    // Park Angle Accessors
    float getParkSteeringAngle() const { return parkSteeringAngle_; }
    void setParkSteeringAngle(float angle) { parkSteeringAngle_ = angle; }

private:
    // Initialization helpers
    bool attachLEDC(const LEDCConfig& cfg);

    // Persistence
    bool saveSweepSummary();

    // Members
    ServoController servo_;
    HallSensorHandler hallSensor_;
    ServoCalibration servoCal_;
    CommandPriority currentPriority_ = CommandPriority::PriorityNormal;
    SystemState currentState_ = SystemState::Booting;
    std::vector<StateTransition> transitionQueue_;
    float parkSteeringAngle_;
    CommandSourceContext context_;

    // Members for ProcessMoveCmd state machine
    bool moveCmdActive_ = false;
    unsigned long moveCmdStartTime_ = 0;
    float moveCmdSlewTime_ = 0.0f;

    // Hall LED blink state
    bool hallLedState_ = false;
    unsigned long hallLedLastToggle_ = 0;
};

#endif //LEG_SUPERVISOR_H