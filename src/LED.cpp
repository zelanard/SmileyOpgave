#include "LED.h"

void updateLEDs()
{
    // Turn off LEDs individually after LED_ON_TIME milli seconds
    unsigned long now = millis();
    if (ledActives[0] && now - ledTimers[0] >= LED_ON_TIME)
    {
        digitalWrite(LED_RED, LOW);
        ledActives[0] = false;
    }
    if (ledActives[1] && now - ledTimers[1] >= LED_ON_TIME)
    {
        digitalWrite(LED_BLUE, LOW);
        ledActives[1] = false;
    }
    if (ledActives[2] && now - ledTimers[2] >= LED_ON_TIME)
    {
        digitalWrite(LED_GREEN, LOW);
        ledActives[2] = false;
    }
    if (ledActives[3] && now - ledTimers[3] >= LED_ON_TIME)
    {
        digitalWrite(LED_YELLOW, LOW);
        ledActives[3] = false;
    }
}