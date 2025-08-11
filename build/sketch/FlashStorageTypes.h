#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\FlashStorageTypes.h"
#pragma once
#include <map>
#include <string>
#include <variant>
#include "DriveConfig.h"  // Grants access to ServoConfig::kTotalMagnets

// --- Calibration Fit Result Struct ---
struct LinearFitResult {
    float slope;
    float intercept;
    float rmse;
    float avg_backlash;
};

struct SweepSummary {
    static constexpr const char* nvs_namespace = "servo_calibration";

    uint32_t cw_center_us[ServoConfig::kTotalMagnets];
    uint32_t ccw_center_us[ServoConfig::kTotalMagnets];
    int16_t backlash_offset[ServoConfig::kTotalMagnets];
    LinearFitResult fit_result;
    float residuals[ServoConfig::kTotalMagnets]; // Per-magnet calibration residuals
    bool validated;
};

using NVSValue = std::variant<int32_t, float, std::string>;

// Serialization helpers for SweepSummary
// Generic serialization interface
std::map<std::string, NVSValue> serializeSummary(const SweepSummary& summary);
// Generic deserialization interface
void deserializeSummary(const std::map<std::string, NVSValue>& kv, SweepSummary& summary);
