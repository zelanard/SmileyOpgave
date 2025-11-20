#include "PowerSave.h"
#include <esp_sleep.h>
#include "Setup.h"
#include "Buttons.h"

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

    uint64_t wakeup_status = esp_sleep_get_ext1_wakeup_status();
    if (wakeup_status != 0)
    {
        auto [buttonName, message, ledPin, ledIndex] = getButtonValues(wakeup_status);
        mqttButtonAction(buttonName, message);
        ledOn(ledPin, ledIndex);
    }
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

std::tuple<char *, char *, int, int> getButtonValues(uint64_t wakeup_status)
{
    if (wakeup_status & (1ULL << BUTTON_RED))
    {
        return {"Red", "Red button pressed", LED_RED, 0};
    }
    if (wakeup_status & (1ULL << BUTTON_BLUE))
    {
        return {"Blue", "Blue button pressed", LED_BLUE, 1};
    }
    if (wakeup_status & (1ULL << BUTTON_GREEN))
    {
        return {"Green", "Green button pressed", LED_GREEN, 2};
    }
    if (wakeup_status & (1ULL << BUTTON_YELLOW))
    {
        return {"Yellow", "Yellow button pressed", LED_YELLOW, 3};
    }
    return {nullptr, nullptr, -1, -1};
}