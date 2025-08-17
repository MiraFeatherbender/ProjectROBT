
#pragma once
#include <stdint.h>
#include "TMC2160.h"

typedef struct {
    uint8_t en_pwm_mode;
    uint8_t shaft;
    uint8_t diag0_error;
    uint8_t mres;
    uint8_t ihold;
    uint8_t irun;
    uint8_t iholddelay;
} TMC2160Config;

uint32_t build_gconf(const TMC2160Config *cfg);
uint32_t build_chopconf(const TMC2160Config *cfg);
uint32_t build_ihold_irun(const TMC2160Config *cfg);

typedef struct {
    uint8_t reg;      // Register address
    uint32_t value;   // Packed register value
} TMC2160InitSetting;

void tmc2160_init(uint16_t icID, const TMC2160InitSetting *settings, size_t count);
