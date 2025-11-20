#ifndef POWERSAVE_H
#define POWERSAVE_H

#include <Arduino.h>
#include "driver/rtc_io.h"

void setupDeepSleep(unsigned long idleTimeSeconds);
void checkIdleAndSleep(unsigned long lastActivityMillis);
std::tuple<char *, char *, int, int> getButtonValues(uint64_t wakeup_status);

#endif
