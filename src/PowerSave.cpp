#include "PowerSave.h"
#include <esp_sleep.h>
#include "Setup.h"

static unsigned long sleepIdleTime = 10; // default seconds

void setupDeepSleep(unsigned long idleTimeSeconds)
{
    sleepIdleTime = idleTimeSeconds;
}

void checkIdleAndSleep(unsigned long lastActivityMillis)
{
    if (millis() - lastActivityMillis >= sleepIdleTime * 1000)
    {
        Serial.println("Idle timeout reached, going to deep sleep...");

        while (
            digitalRead(BUTTON_RED) == LOW
            || digitalRead(BUTTON_BLUE) == LOW
            || digitalRead(BUTTON_GREEN) == LOW
            || digitalRead(BUTTON_YELLOW) == LOW
        )
        {
            Serial.println("Waiting for button release before sleep...");
            delay(100);
        }

        Serial.flush();
        esp_deep_sleep_start();
    }
}