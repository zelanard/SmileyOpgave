#include "Buttons.h"

void ledOn(int ledPin, int ledIndex)
{
    digitalWrite(ledPin, HIGH);
    ledTimers[ledIndex] = millis();
    ledActives[ledIndex] = true;
    lastActivity = millis();
}

void mqttButtonAction(const char *buttonName, const char *message)
{
    Serial.println(message);
    char *payload = CreateJson(buttonName, GetLocalTime());
    Serial.println(payload);
    mqtt_publish(payload);
}

// Button press handlers

void onRedPress()
{
    mqttButtonAction("Red", "Red button pressed");
    ledOn(LED_RED, 0);
}

void onBluePress()
{
    mqttButtonAction("Blue", "Blue button pressed");
    ledOn(LED_BLUE, 1);
}

void onGreenPress()
{
    mqttButtonAction("Green", "Green button pressed");
    ledOn(LED_RED, 2);
}

void onYellowPress()
{
    mqttButtonAction("Yellow", "Yellow button pressed");
    ledOn(LED_YELLOW, 3);
}

void AttachButtonHandlers()
{
    // --- Attach button handlers ---
    buttonRed.attachClick(onRedPress);
    buttonBlue.attachClick(onBluePress);
    buttonGreen.attachClick(onGreenPress);
    buttonYellow.attachClick(onYellowPress);
}

void loopButtons()
{
    buttonRed.tick();
    buttonBlue.tick();
    buttonGreen.tick();
    buttonYellow.tick();
}