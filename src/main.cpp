#include <Arduino.h>
#include <WiFi.h>
#include <OneButton.h>
#include <PubSubClient.h>
#include "Json.h"
#include "SetupTime.h"

// MQTT broker settings
const char *mqtt_server = "wilson.local";
const int mqtt_port = 1883;
const char *mqtt_topic = "esp32/tatiana_jonas/button";

// LEDs
const int LED_RED = 5;
const int LED_BLUE = 19;
const int LED_GREEN = 21;
const int LED_YELLOW = 23;

// Buttons
const int BUTTON_RED = 35;
const int BUTTON_BLUE = 34;
const int BUTTON_GREEN = 32;
const int BUTTON_YELLOW = 33;

// Create  a globalOneButton objects
OneButton buttonRed(BUTTON_RED, false, true);
OneButton buttonBlue(BUTTON_BLUE, false, true);
OneButton buttonGreen(BUTTON_GREEN, false, true);
OneButton buttonYellow(BUTTON_YELLOW, false, true);

void onRedPress()
{
    Serial.println("🔴 Red button pressed");
    digitalWrite(LED_RED, HIGH);
}

void onBluePress()
{
    Serial.println("🔵 Blue button pressed");
    digitalWrite(LED_BLUE, HIGH);
}

void onGreenPress()
{
    Serial.println("🟢 Green button pressed");
    digitalWrite(LED_GREEN, HIGH);
}

void onYellowPress()
{
    Serial.println("🟡 Yellow button pressed");
    digitalWrite(LED_YELLOW, HIGH);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // LED setup
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);

    // Button setup
    pinMode(BUTTON_RED, INPUT);
    pinMode(BUTTON_BLUE, INPUT);
    pinMode(BUTTON_GREEN, INPUT);
    pinMode(BUTTON_YELLOW, INPUT);

    // Attach button click handlers
    buttonRed.attachClick(onRedPress);
    buttonBlue.attachClick(onBluePress);
    buttonGreen.attachClick(onGreenPress);
    buttonYellow.attachClick(onYellowPress);

    // Setup wifi and time
    TrySetupWifi();
    TrySetupTime();

    Serial.println("System Ready. Waiting for button presses...");
}

void loop()
{
    // Handle button events
    buttonRed.tick();
    buttonBlue.tick();
    buttonGreen.tick();
    buttonYellow.tick();

    // Reconnect to the wifi if it is disconnected
    TrySetupWifi();

    // Set the time up if it is not setup
    TrySetupTime();
}
