#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\ServoCalibration.cpp"
#include "ServoCalibration.h" 
#include <Arduino.h>  // Needed if using micros(), millis(), etc.
#include <algorithm>


ServoCalibration::ServoCalibration(ServoController& servo, const ServoConfig& servoCFG)
    : servo_(servo), servoCFG_(servoCFG), direction(CW), step_idx(0) {
    // Optional init logic
} 

bool ServoCalibration::begin() { 
    state_ = SWEEP_IDLE;

    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        auto& profile = magnet_profiles_[i];
        profile.angle_deg = static_cast<int8_t>(i * 30 + 45);
    }

    return true; 
}

void ServoCalibration::run() {
    switch (state_) {
        case SWEEP_IDLE:
            servo_.setAngleRaw(0.0f); // 0°
            if (servo_.getPulseUS() <= 510) {
                step_idx = 0;
                direction = CW;
                state_ = SWEEP_CW_ACTIVE;
                servo_.setAngleRaw(270.0f);
            }
            break;

        case SWEEP_CW_ACTIVE:
            if (servo_.getPulseUS() >= 2490) {
                direction = CCW;
                state_ = SWEEP_CCW_ACTIVE;
                servo_.setAngleRaw(0.0f);
            }
            break;

        case SWEEP_CCW_ACTIVE:
            if (servo_.getPulseUS() <= 510) {
                state_ = SWEEP_VALIDATE;
            }
            break;

        case SWEEP_VALIDATE:
            if (validateSweep()) {
                state_ = SWEEP_COMPLETE;
            } else {
                for (const auto& profile : magnet_profiles_) {
                    if (profile.retry_count > 3) { //3 is placeholder
                        state_ = SWEEP_FAIL;
                        return;
                    }
                }
                state_ = SWEEP_IDLE; // Retry logic resumes
            }
            break;

        case SWEEP_FAIL:
            // Trigger blinking indicator here
            break;

        case SWEEP_COMPLETE:
            // Calibration successful            
            finalizeSweepSummary();
            break;
    }
}

void ServoCalibration::logSweepEvent(const SweepEvent& event) {
    uint8_t idx = PWMtoMagnetIDX(event.us_value);
    auto& profile = magnet_profiles_[idx];
    uint8_t i = step_idx++ % 4;  // Wrap index for safe array access

    // Only overwrite if this direction hasn't already been marked valid
    if (!profile.valid[direction]) {
        switch (direction) {
            case CW:
                profile.cw_sweep[i] = event.us_value; 
                profile.cw_pattern_bits <<= 2;
                profile.cw_pattern_bits |= (event.hall_bits & 0x03);
                break;

            case CCW:
                profile.ccw_sweep[i] = event.us_value;
                profile.ccw_pattern_bits <<= 2;
                profile.ccw_pattern_bits |= (event.hall_bits & 0x03);
                break;
        }
    
        profile.retry_count++;
    }
}

uint8_t ServoCalibration::PWMtoMagnetIDX(uint16_t pwm_value){
    uint16_t min = servoCFG_.pulse_min_us;
    uint16_t max = servoCFG_.pulse_max_us;
    uint16_t bins = servoCFG_.angle_max_deg / servoCFG_.magnet_spacing_deg;
    int MagnetIDX = floor((pwm_value - min) * (static_cast<float>(bins) / static_cast<float>(max - min))) - 1;
    return std::clamp(MagnetIDX, 0, ServoConfig::kTotalMagnets - 1);
}

bool ServoCalibration::validateSweep() {
    bool all_valid = true;
    for (auto& profile : magnet_profiles_) {
        bool cw_ok = (profile.cw_pattern_bits == expected_cw_pattern);
        bool ccw_ok = (profile.ccw_pattern_bits == expected_ccw_pattern);
        profile.valid[CW] = cw_ok;
        profile.valid[CCW] = ccw_ok;
        all_valid &= (cw_ok && ccw_ok);
    }
    return all_valid;
}

void ServoCalibration::computeCentersAndBacklash(std::vector<float>& ref_angles, std::vector<float>& center_pulses, std::vector<float>& backlash_offsets) const {
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        auto& profile = magnet_profiles_[i];
        float ref_angle = servoCFG_.motion_window_min + i * servoCFG_.magnet_spacing_deg;
        float center = 0.5f * (profile.cw_center_us + profile.ccw_center_us);
        float backlash = std::abs(profile.cw_center_us - profile.ccw_center_us);

        ref_angles.push_back(ref_angle);
        center_pulses.push_back(center);
        backlash_offsets.push_back(backlash);
    }
}

LinearFitResult ServoCalibration::fitMeasuredCenters(const std::vector<float>& ref_angles, const std::vector<float>& center_pulses, const std::vector<float>& backlash_offsets) const {
    size_t n = ref_angles.size();
    if (n == 0) return {0, 0, 0, 0};

    float sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;
    for (size_t i = 0; i < n; ++i) {
        sum_x += ref_angles[i];
        sum_y += center_pulses[i];
        sum_xx += ref_angles[i] * ref_angles[i];
        sum_xy += ref_angles[i] * center_pulses[i];
    }
    float slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
    float intercept = (sum_y - slope * sum_x) / n;

    float rmse = 0;
    for (size_t i = 0; i < n; ++i) {
        float pred = slope * ref_angles[i] + intercept;
        rmse += (center_pulses[i] - pred) * (center_pulses[i] - pred);
    }
    rmse = sqrt(rmse / n);

    float avg_backlash = 0;
    for (const auto& b : backlash_offsets) avg_backlash += b;
    avg_backlash /= n;

    return {slope, intercept, rmse, avg_backlash};
}

void ServoCalibration::finalizeSweepSummary() {
    // Update magnet profile centers and backlash
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        auto& profile = magnet_profiles_[i];
        profile.cw_center_us = (profile.cw_sweep[1] + profile.cw_sweep[2]) / 2;
        profile.ccw_center_us = (profile.ccw_sweep[1] + profile.ccw_sweep[2]) / 2;
        profile.backlash_offset_us = std::abs(profile.cw_center_us - profile.ccw_center_us);

        summary_.cw_center_us[i] = profile.cw_center_us;
        summary_.ccw_center_us[i] = profile.ccw_center_us;
        summary_.backlash_offset[i] = profile.backlash_offset_us;

        // Residual calculation
        float measured_pulse = (profile.cw_center_us + profile.ccw_center_us) / 2;
        float ideal_pulse = referencePulseFromIndex(i);
        summary_.residuals[i] = measured_pulse - ideal_pulse;
    }

    // Modular fit and storage
    std::vector<float> ref_angles, center_pulses, backlash_offsets;
    computeCentersAndBacklash(ref_angles, center_pulses, backlash_offsets);
    LinearFitResult fit = fitMeasuredCenters(ref_angles, center_pulses, backlash_offsets);
    summary_.fit_result = fit;
}


uint32_t ServoCalibration::referencePulseFromIndex(uint8_t magnet_idx) { 
    float angle_span = servoCFG_.angle_max_deg - servoCFG_.angle_min_deg;
    float pulse_span = servoCFG_.pulse_max_us - servoCFG_.pulse_min_us;

    float bins = angle_span / servoCFG_.magnet_spacing_deg;
    float slope = pulse_span / bins;

    float offset_bins = (servoCFG_.motion_window_min - servoCFG_.angle_min_deg) / servoCFG_.magnet_spacing_deg;
    float offset_us = offset_bins * slope;
    float intercept = offset_us + servoCFG_.pulse_min_us;

    return static_cast<uint32_t>(magnet_idx * slope + intercept);
}

/*
void ServoCalibration::finalizeSweepSummary() {
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        auto& profile = magnet_profiles_[i];

        profile.cw_center_us = (profile.cw_sweep[1] + profile.cw_sweep[2]) / 2;
        profile.ccw_center_us = (profile.ccw_sweep[1] + profile.ccw_sweep[2]) / 2;
        profile.backlash_offset_us = std::abs(profile.cw_center_us - profile.ccw_center_us);

        summary_.cw_center_us[i] = profile.cw_center_us;
        summary_.ccw_center_us[i] = profile.ccw_center_us;
        summary_.backlash_offset[i] = profile.backlash_offset_us;
    }
}
*/

SweepSummary ServoCalibration::getSweepSummary(){
    return summary_;
}