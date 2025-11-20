#include "Setup.h"
#include "Buttons.h"
#include "LED.h"

void setup()
{
    // Indicate system is starting
    pinMode(LED_BUILT_IN, OUTPUT);
    digitalWrite(LED_BUILT_IN, HIGH);

    // Start Serial for debugging
    Serial.begin(115200);
    delay(1000);

    // Setup pins and button handlers
    PinModeSetup();
    AttachButtonHandlers();

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
    // handle button presses
    loopButtons();

    // update LEDs
    updateLEDs();

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
