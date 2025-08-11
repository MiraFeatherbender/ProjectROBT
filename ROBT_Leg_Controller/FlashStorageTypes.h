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


// --- Helper serialization/deserialization for LinearFitResult ---
std::map<std::string, NVSValue> serializeFitResult(const LinearFitResult& fit);
void deserializeFitResult(const std::map<std::string, NVSValue>& kv, LinearFitResult& fit);

// --- SweepSummary serialization/deserialization ---
std::map<std::string, NVSValue> serializeSummary(const SweepSummary& summary);
void deserializeSummary(const std::map<std::string, NVSValue>& kv, SweepSummary& summary);

// --- FitResultSummary type and serialization/deserialization ---
struct FitResultSummary {
    static constexpr const char* nvs_namespace = "servo_calibration";
    LinearFitResult fit_result;
};
std::map<std::string, NVSValue> serializeSummary(const FitResultSummary& summary);
void deserializeSummary(const std::map<std::string, NVSValue>& kv, FitResultSummary& summary);
