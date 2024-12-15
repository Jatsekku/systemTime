#include <stdbool.h>
#include <sys/time.h>
#include <stdint.h>
#include <stddef.h>

#include "logger.h"
LOGGER_REGISTER_MODULE("systemTime", LOG_LEVEL_DBG);

#define USEC_PER_SEC 1000000
#define USEC_PER_MSEC 1000

struct systemTimeContext {
	uint64_t last_freezed_epoch_us;
	uint64_t freezed_period_sum;
	bool is_epoch_freezed;
};

static struct systemTimeContext context = {
	.last_freezed_epoch_us = 0,
	.freezed_period_sum = 0,
	.is_epoch_freezed = false,
};

uint64_t systemTime_getEpochUs(void) {
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return (uint64_t)(current_time.tv_sec * USEC_PER_SEC) + (uint64_t)current_time.tv_usec; 
}

uint32_t systemTime_getEpochMs(void) {
	return (uint32_t)(systemTime_getEpochUs() / USEC_PER_MSEC);
}

uint64_t systemTime_getFreezableEpochUs(void) {
	if (context.is_epoch_freezed) {
		return context.last_freezed_epoch_us;
	}

	return systemTime_getEpochUs() - context.freezed_period_sum;
}

uint32_t systemTime_getFreezableEpochMs(void) {
	return (uint32_t)(systemTime_getFreezableEpochUs() / USEC_PER_MSEC);
}

void systemTime_freezeEpoch(void) {
	if (context.is_epoch_freezed) {
		return;
	}

	context.last_freezed_epoch_us = systemTime_getEpochUs();
	context.is_epoch_freezed = true;
}

void systemTime_unfreezeEpoch(void) {
	if (!context.is_epoch_freezed) {
		return;
	}

	const uint64_t epoch_us_now = systemTime_getEpochUs();
	context.freezed_period_sum += epoch_us_now - context.last_freezed_epoch_us; 
	context.is_epoch_freezed = false;
}
