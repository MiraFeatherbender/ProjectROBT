#include "FlashStorageTypes.h"
#include "DriveConfig.h"


// --- Helper serialization/deserialization for LinearFitResult ---
std::map<std::string, NVSValue> serializeFitResult(const LinearFitResult& fit) {
    return {
        {"slope", fit.slope},
        {"intercept", fit.intercept},
        {"rmse", fit.rmse},
        {"avg_backlash", fit.avg_backlash}
    };
}

void deserializeFitResult(const std::map<std::string, NVSValue>& kv, LinearFitResult& fit) {
    fit.slope = std::get<float>(kv.at("slope"));
    fit.intercept = std::get<float>(kv.at("intercept"));
    fit.rmse = std::get<float>(kv.at("rmse"));
    fit.avg_backlash = std::get<float>(kv.at("avg_backlash"));
}

// --- SweepSummary serialization/deserialization ---
std::map<std::string, NVSValue> serializeSummary(const SweepSummary& summary) {
    std::map<std::string, NVSValue> kv;
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        kv["cw_center_us_" + std::to_string(i)] = static_cast<int32_t>(summary.cw_center_us[i]);
        kv["ccw_center_us_" + std::to_string(i)] = static_cast<int32_t>(summary.ccw_center_us[i]);
        kv["backlash_offset_" + std::to_string(i)] = static_cast<int32_t>(summary.backlash_offset[i]);
        kv["residual_" + std::to_string(i)] = summary.residuals[i];
    }
    auto fitKv = serializeFitResult(summary.fit_result);
    kv.insert(fitKv.begin(), fitKv.end());
    kv["validated"] = summary.validated ? 1.0f : 0.0f;
    return kv;
}

void deserializeSummary(const std::map<std::string, NVSValue>& kv, SweepSummary& summary) {
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        summary.cw_center_us[i] = std::get<int32_t>(kv.at("cw_center_us_" + std::to_string(i)));
        summary.ccw_center_us[i] = std::get<int32_t>(kv.at("ccw_center_us_" + std::to_string(i)));
        summary.backlash_offset[i] = static_cast<int16_t>(std::get<int32_t>(kv.at("backlash_offset_" + std::to_string(i))));
        summary.residuals[i] = std::get<float>(kv.at("residual_" + std::to_string(i)));
    }
    deserializeFitResult(kv, summary.fit_result);
    summary.validated = (std::get<float>(kv.at("validated")) > 0.5f);
}

// --- FitResultSummary serialization/deserialization ---
std::map<std::string, NVSValue> serializeSummary(const FitResultSummary& summary) {
    return serializeFitResult(summary.fit_result);
}

void deserializeSummary(const std::map<std::string, NVSValue>& kv, FitResultSummary& summary) {
    deserializeFitResult(kv, summary.fit_result);
}
