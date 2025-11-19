#include "PowerSave.h"
#include <esp_sleep.h>
#include "Setup.h"

static unsigned long sleepIdleTime = 10; // default seconds

void setupDeepSleep(unsigned long idleTimeSeconds)
{
    sleepIdleTime = idleTimeSeconds;

    uint64_t wakeup_pins =
        (1ULL << BUTTON_RED) |
        (1ULL << BUTTON_BLUE) |
        (1ULL << BUTTON_GREEN) |
        (1ULL << BUTTON_YELLOW);

    esp_sleep_enable_ext1_wakeup(wakeup_pins, ESP_EXT1_WAKEUP_ANY_HIGH);
}

void checkIdleAndSleep(unsigned long lastActivityMillis)
{
    if (millis() - lastActivityMillis >= sleepIdleTime * 1000UL)
    {
        Serial.println("Idle timeout reached, going to deep sleep...");
        Serial.flush();
        esp_deep_sleep_start();
    }
}