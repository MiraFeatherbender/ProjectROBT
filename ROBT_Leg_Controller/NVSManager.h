#include "FlashStorageTypes.h"

class NVSManager {
public:
    static bool storeSweepSummary(const SweepSummary& summary);
    static SweepSummary retrieveSweepSummary();
};