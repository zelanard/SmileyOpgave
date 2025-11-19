#include "SetupTime.h"

bool TimeIsSetup = false;

// NTP server
const char *ntpServer = "pool.ntp.org";

// Europe/Copenhagen timezone (CET/CEST)
const char *timezone = "CET-1CEST,M3.5.0/2,M10.5.0/3";

bool SetupTime()
{
    // First get UTC from NTP
    configTime(0, 0, ntpServer); // offsets = 0 because we'll use TZ instead

    Serial.println("Waiting for NTP time…");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo))
    { // actually still UTC at this point
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nGot NTP time (UTC)");

    // Now set time zone
    setenv("TZ", timezone, 1); // set TZ env var
    tzset();                   // apply it

    return true;
}

void PrintLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }

    // Example: 2025-11-19 14:23:05 CET
    Serial.print("Local time: ");
    Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n",
                  timeinfo.tm_year + 1900,
                  timeinfo.tm_mon + 1,
                  timeinfo.tm_mday,
                  timeinfo.tm_hour,
                  timeinfo.tm_min,
                  timeinfo.tm_sec);
}

void TrySetupTime()
{
    // Setup time
    if (ConnectedToWifi && !TimeIsSetup)
    {
        TimeIsSetup = SetupTime();
    }
}