#pragma once
#include <stdint.h>

uint64_t systemTime_getEpochUs(void);
uint32_t systemTime_getEpochMs(void);
uint64_t systemTime_getFreezableEpochUs(void);
uint32_t systemTime_getFreezableEpochMs(void);
void systemTime_freezeEpoch(void);
void systemTime_unfreezeEpoch(void);
