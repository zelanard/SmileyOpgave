#include "PowerSave.h"
#include <esp_sleep.h>

static unsigned long sleepIdleTime = 10; // default seconds

void setupDeepSleep(unsigned long idleTimeSeconds) {
    sleepIdleTime = idleTimeSeconds;

    // Example: Wake up on any button press
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, 0); // replace with actual pin
    // esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 0); // LOW = pressed
}

void checkIdleAndSleep(unsigned long lastActivityMillis) {
    if (millis() - lastActivityMillis >= sleepIdleTime * 1000) {
        Serial.println("Idle timeout reached, going to deep sleep...");
        delay(100); // allow Serial to print
        esp_deep_sleep_start();
    }
}
