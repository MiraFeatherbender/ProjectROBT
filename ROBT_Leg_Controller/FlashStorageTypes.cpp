#include "FlashStorageTypes.h"
#include "DriveConfig.h"

std::map<std::string, NVSValue> serializeSummary(const SweepSummary& summary) {
    std::map<std::string, NVSValue> kv;
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        kv["cw_center_us_" + std::to_string(i)] = static_cast<int32_t>(summary.cw_center_us[i]);
        kv["ccw_center_us_" + std::to_string(i)] = static_cast<int32_t>(summary.ccw_center_us[i]);
        kv["backlash_offset_" + std::to_string(i)] = static_cast<int32_t>(summary.backlash_offset[i]);
        kv["residual_" + std::to_string(i)] = summary.residuals[i];
    }
    kv["slope"] = summary.fit_result.slope;
    kv["intercept"] = summary.fit_result.intercept;
    kv["rmse"] = summary.fit_result.rmse;
    kv["avg_backlash"] = summary.fit_result.avg_backlash;
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
    summary.fit_result.slope = std::get<float>(kv.at("slope"));
    summary.fit_result.intercept = std::get<float>(kv.at("intercept"));
    summary.fit_result.rmse = std::get<float>(kv.at("rmse"));
    summary.fit_result.avg_backlash = std::get<float>(kv.at("avg_backlash"));
    summary.validated = (std::get<float>(kv.at("validated")) > 0.5f);
}
