#include "Buttons.h"

void ledOn(int ledPin, int ledIndex)
{
    digitalWrite(ledPin, HIGH);
    ledTimers[ledIndex] = millis();
    ledActives[ledIndex] = true;
    lastActivity = millis();
}

void mqttPublishButtonPress(const char *buttonName, const char *message)
{
    Serial.println(message);
    char *payload = CreateJson(buttonName, GetLocalTime());
    Serial.println(payload);
    mqtt_publish(payload);
}

void onRedPress()
{
    mqttPublishButtonPress("Red", "Red button pressed");
    ledOn(LED_RED, 0);
}

void onBluePress()
{
    mqttPublishButtonPress("Blue", "Blue button pressed");
    ledOn(LED_BLUE, 1);
}

void onGreenPress()
{
    mqttPublishButtonPress("Green", "Green button pressed");
    ledOn(LED_RED, 2);
}

void onYellowPress()
{
    mqttPublishButtonPress("Yellow", "Yellow button pressed");
    ledOn(LED_YELLOW, 3);
}