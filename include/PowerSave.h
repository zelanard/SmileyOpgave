#pragma once
#ifndef POWERSAVE_H
#define POWERSAVE_H

#include <Arduino.h>
#include "driver/rtc_io.h"

// Setup deep sleep with specified idle time in seconds
void setupDeepSleep(unsigned long idleTimeSeconds);

// Check if the system has been idle for the specified duration and enter deep sleep if so
void checkIdleAndSleep(unsigned long lastActivityMillis);

// Retrieve button values from wakeup status
std::tuple<char *, char *, int, int> getButtonValues(uint64_t wakeup_status);

#endif
