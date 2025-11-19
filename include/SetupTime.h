#pragma once
#include "time.h"
#include <arduino.h>
#include "SetupWifi.h"

extern bool TimeIsSetup;

bool SetupTime();
char* GetLocalTime();
void TrySetupTime();
char* getFormattedTime(struct tm timeinfo);