#include "NVSManager.h"
#include <Arduino.h>


bool NVSManager::Summary(const SweepSummary& summary) {
    Serial.println("[NVSManager] Stub: storeSweepSummary called.");
    printSummaryToSerial(summary);
    return true;
}
