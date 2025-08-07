#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\NVSManager.h"
#ifndef NVS_MANAGER_H
#define NVS_MANAGER_H

#include "FlashStorageTypes.h"

class NVSManager {
public:
    static bool storeSweepSummary(const SweepSummary& summary);
    static bool retrieveSweepSummary(SweepSummary& summary);
    static void printSweepSummaryToSerial(const SweepSummary& summary);
};

#endif // NVS_MANAGER_H