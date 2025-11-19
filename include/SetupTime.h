#pragma once
#include "time.h"
#include <arduino.h>
#include "SetupWifi.h"

extern bool TimeIsSetup;

bool SetupTime();
String GetLocalTime();
void TrySetupTime();
String getFormattedTime(const struct tm &timeinfo);