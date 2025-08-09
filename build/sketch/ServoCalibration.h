#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\ServoCalibration.h"
#ifndef SERVO_CALIBRATION_H
#define SERVO_CALIBRATION_H

#include <vector>
#include "ServoController.h"
#include "DriveConfig.h"
#include "FlashStorageTypes.h"
// --- Enums ---

enum HallEvent { 
    FIELD_ENTRY,    // 01 or 10
    CENTER_ENTRY,   // 00
    CENTER_EXIT,    // 10 or 01
    FIELD_EXIT      // 00
};

enum SweepDirection {
    CW,    // Field_Entry = 10
    CCW    // Field_Entry = 01
};

enum StateMachine {
    SWEEP_IDLE,
    SWEEP_CW_ACTIVE,
    SWEEP_CCW_ACTIVE,
    SWEEP_VALIDATE,
    SWEEP_FAIL,
    SWEEP_COMPLETE
};

// --- Structs ---

struct SweepEvent {
    uint8_t hall_bits;        // Raw bit pair from GPIO (e.g. 00, 01, 10)
    uint32_t us_value;        // Captured LEDC PWM value
};

struct MagnetSweepProfile {
    int8_t angle_deg;               // Absolute position, e.g. -90 → +90
    int16_t cw_sweep[4];            // PWM Storage ordered FIELD_ENTRY → FIELD_EXIT
    int16_t ccw_sweep[4];           // Reverse order
    uint8_t cw_pattern_bits;        // 0x84 = 10000100 = valid
    uint8_t ccw_pattern_bits;       // 0x48 = 01001000 = valid
    int cw_center_us;               // Computed center PWM for CW
    int ccw_center_us;              // Computed center PWM for CCW
    int16_t backlash_offset_us;     // Delta between CW and CCW centers
    uint8_t retry_count = 0;        // Number of resweep attempts
    bool valid[2] = {0, 0};         // Sweep integrity flags [CW], [CCW]
};

// --- Servo Calibration Class ---

class ServoCalibration {
public:
    explicit ServoCalibration(ServoController& servo, const ServoConfig& servoCFG);

    bool begin();
    void run();                         // Initiates 0 → 270 → 0 sweep
    bool validateSweep();               // True if all 14 sequences are valid
    SweepSummary getSweepSummary();     // Returns SweepSummary for flash storage
    void logSweepEvent(const SweepEvent& event);
   
private:
    uint8_t PWMtoMagnetIDX(uint16_t pwm_value);
    uint32_t referencePulseFromIndex(uint8_t magnet_idx);
    void finalizeSweepSummary();

    // Calibration fit and analysis helpers
    void computeCentersAndBacklash(std::vector<float>& ref_angles, std::vector<float>& center_pulses, std::vector<float>& backlash_offsets) const;
    LinearFitResult fitMeasuredCenters(const std::vector<float>& ref_angles, const std::vector<float>& center_pulses, const std::vector<float>& backlash_offsets) const;

    ServoController& servo_;            // Servo interface for getPulseUS and setAngleRaw
    const ServoConfig& servoCFG_;
    MagnetSweepProfile magnet_profiles_[ServoConfig::kTotalMagnets];
    SweepDirection direction;
    uint8_t step_idx;

    static constexpr uint8_t expected_cw_pattern = 0x84;
    static constexpr uint8_t expected_ccw_pattern = 0x48;
    StateMachine state_;
    SweepSummary summary_;

};

#endif // SERVO_CALIBRATION_H