#include "TMC2160Config.h"

uint32_t build_gconf(const TMC2160Config *cfg) {
    uint32_t value = 0;
    if (cfg->en_pwm_mode) value |= TMC2160_GCONF_EN_PWM_MODE;
    if (cfg->shaft)       value |= TMC2160_GCONF_SHAFT;
    if (cfg->diag0_error) value |= TMC2160_GCONF_DIAG0_ERROR;
    // Add more fields as needed using TMC2160.h macros
    return value;
}

uint32_t build_chopconf(const TMC2160Config *cfg) {
    uint32_t value = 0;
    value |= (cfg->mres << TMC2160_CHOPCONF_MRES_SHIFT) & TMC2160_CHOPCONF_MRES_MASK;
    // Add more fields as needed using TMC2160.h macros
    return value;
}

uint32_t build_ihold_irun(const TMC2160Config *cfg) {
    uint32_t value = 0;
    value |= (cfg->ihold << TMC2160_IHOLD_SHIFT);
    value |= (cfg->irun << TMC2160_IRUN_SHIFT);
    value |= (cfg->iholddelay << TMC2160_IHOLDDELAY_SHIFT);
    // Add more fields as needed using TMC2160.h macros
    return value;
}

// Modular initialization function
extern "C" void tmc2160_writeRegister(uint16_t icID, uint8_t address, int32_t value); // Ensure linkage to API

void tmc2160_init(uint16_t icID, const TMC2160InitSetting *settings, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        tmc2160_writeRegister(icID, settings[i].reg, settings[i].value);
    }
}
