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

String GetLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        char* val = "Failed to obtain time"; 
        return val;
    }

    // Example: 2025-11-19 14:23:05 CET
    return getFormattedTime(timeinfo);
}

String getFormattedTime(const struct tm &timeinfo)
{
    char buffer[25];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buffer);  // copy into Arduino String
}


void TrySetupTime()
{
    // Setup time
    if (ConnectedToWifi && !TimeIsSetup)
    {
        TimeIsSetup = SetupTime();
    }
}