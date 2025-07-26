enum HallEvent {
    FIELD_ENTRY,
    CENTER_ENTRY,
    CENTER_EXIT,
    FIELD_EXIT
};

enum SweepDirection {
    CW,
    CCW
};

struct SweepEvent {
    HallEvent type;         // Transition classification
    uint32_t pwm_value;     // LEDC PWM value at time of edge
    bool valid;             // Flag set during post-validation
};

struct MagnetSweepProfile {
    int8_t angle_deg;               // Absolute position, e.g. -90 → +90
    SweepEvent cw_sweep[4];        // Ordered FIELD_ENTRY → FIELD_EXIT
    SweepEvent ccw_sweep[4];       // Reverse order
    uint16_t cw_pattern_bits;      // Optional bit signature for sweep recognition
    uint16_t ccw_pattern_bits;
    uint32_t cw_center_pwm;        // Computed center PWM for CW
    uint32_t ccw_center_pwm;       // Computed center PWM for CCW
    int16_t backlash_offset_pwm;   // Delta between CW and CCW centers
    uint8_t retry_count;           // Number of resweep attempts
    bool valid[2];                 // Sweep integrity flags [CW], [CCW]
};

struct SweepTracker {
    uint8_t magnet_index;       // Which magnet is being swept
    SweepDirection direction;
};

void logSweepEvent(uint8_t magnet_idx, SweepDirection dir, SweepEvent event);

HallEvent classifyHallEdge(uint8_t prev_state, uint8_t curr_state, bool startingWithNorth);

bool validateSweep(uint8_t magnet_idx, SweepDirection dir);

void runFullSweep();                  // Initiates 0 → 270 → 0 sweep
void advanceSweepTracker();          // Advances to next magnet + direction
bool allSweepsValid();               // True if all 14 sequences are valid
void retryFailedSweeps();            // Reschedule any failed profiles