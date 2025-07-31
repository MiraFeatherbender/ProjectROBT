#ifndef FLASH_STORAGE_TYPES_H
#define FLASH_STORAGE_TYPES_H

#include "DriveConfig.h"  // Grants access to ServoConfig::kTotalMagnets

struct SweepSummary {
    uint32_t cw_center_us[ServoConfig::kTotalMagnets];
    uint32_t ccw_center_us[ServoConfig::kTotalMagnets];
    int16_t backlash_offset[ServoConfig::kTotalMagnets];
    float slope;
    float intercept;
    float linearity_rmse;
    bool validated;
};

#endif // FLASH_STORAGE_TYPES_H 