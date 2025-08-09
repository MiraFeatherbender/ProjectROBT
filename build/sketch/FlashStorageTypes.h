#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\FlashStorageTypes.h"
#ifndef FLASH_STORAGE_TYPES_H
#define FLASH_STORAGE_TYPES_H

#include "DriveConfig.h"  // Grants access to ServoConfig::kTotalMagnets

// --- Calibration Fit Result Struct ---
struct LinearFitResult {
    float slope;
    float intercept;
    float rmse;
    float avg_backlash;
};

struct SweepSummary {
    uint32_t cw_center_us[ServoConfig::kTotalMagnets];
    uint32_t ccw_center_us[ServoConfig::kTotalMagnets];
    int16_t backlash_offset[ServoConfig::kTotalMagnets];
    LinearFitResult fit_result;
    float residuals[ServoConfig::kTotalMagnets]; // Per-magnet calibration residuals
    bool validated;
};

#endif // FLASH_STORAGE_TYPES_H 