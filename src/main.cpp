#include "Setup.h"
#include "Buttons.h"

void setup()
{
    // Indicate system is starting
    pinMode(LED_BUILT_IN, OUTPUT);
    digitalWrite(LED_BUILT_IN, HIGH);

    // Start Serial for debugging
    Serial.begin(115200);
    delay(1000);

    // --- LED setup ---
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);

    // --- Button setup (use INPUT_PULLUP for active LOW buttons) ---
    pinMode(BUTTON_RED, INPUT_PULLUP);
    pinMode(BUTTON_BLUE, INPUT_PULLUP);
    pinMode(BUTTON_GREEN, INPUT_PULLUP);
    pinMode(BUTTON_YELLOW, INPUT_PULLUP);

    // --- Attach button handlers ---
    buttonRed.attachClick(onRedPress);
    buttonBlue.attachClick(onBluePress);
    buttonGreen.attachClick(onGreenPress);
    buttonYellow.attachClick(onYellowPress);

    // setup wifi and time
    TrySetupWifi();
    TrySetupTime();
    TrySetupMQTT();

    // initialize last activity and setup deep sleep
    lastActivity = millis();
    setupDeepSleep(10);

    // Indicate system is ready
    Serial.println("System Ready. Waiting for button presses...");
    digitalWrite(LED_BUILT_IN, LOW);
}

void loop()
{
    // Update button states
    buttonRed.tick();
    buttonBlue.tick();
    buttonGreen.tick();
    buttonYellow.tick();

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

    // reconnect to wifi
    TrySetupWifi();

    // reset time
    TrySetupTime();

    // keep mqtt connection alive
    TrySetupMQTT();
    mqtt_loop();

    // Check idle and possibly sleep
    checkIdleAndSleep(lastActivity);
}
