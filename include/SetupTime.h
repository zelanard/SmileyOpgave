#pragma once
#include "time.h"
#include <arduino.h>
#include "SetupWifi.h"

extern bool TimeIsSetup;

bool SetupTime();
void PrintLocalTime();
void TrySetupTime();