#include "NVSManager.h"
#include <Arduino.h>

bool NVSManager::storeSweepSummary(const SweepSummary& summary) {
    Serial.println("[NVSManager] Stub: storeSweepSummary called.");
    printSweepSummaryToSerial(summary);
    return true;
}

bool NVSManager::retrieveSweepSummary(SweepSummary& summary) {
    Serial.println("[NVSManager] Stub: retrieveSweepSummary called. Returning default SweepSummary.");
    // For now, just zero the struct
    memset(&summary, 0, sizeof(SweepSummary));
    return true;
}

void NVSManager::printSweepSummaryToSerial(const SweepSummary& summary) {
    Serial.println("[NVSManager] SweepSummary contents:");
    for (int i = 0; i < ServoConfig::kTotalMagnets; ++i) {
        Serial.print("  Magnet "); Serial.print(i);
        Serial.print(": CW center = "); Serial.print(summary.cw_center_us[i]);
        Serial.print(", CCW center = "); Serial.print(summary.ccw_center_us[i]);
        Serial.print(", Backlash = "); Serial.println(summary.backlash_offset[i]);
    }
    Serial.print("  Slope: "); Serial.println(summary.fit_result.slope);
    Serial.print("  Intercept: "); Serial.println(summary.fit_result.intercept);
    Serial.print("  Linearity RMSE: "); Serial.println(summary.fit_result.rmse);
    Serial.print("  Validated: "); Serial.println(summary.validated ? "true" : "false");
}
