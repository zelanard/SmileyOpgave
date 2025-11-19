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

unsigned long ledTimers[4] = {0, 0, 0, 0};
bool ledActives[4] = {false, false, false, false};
const unsigned long LED_ON_TIME = 3000;

void onRedPress()
{
    Serial.println("Red button pressed");
    Serial.println(CreateJson("Red", GetLocalTime()));
    digitalWrite(LED_RED, HIGH);
    ledTimers[0] = millis();
    ledActives[0] = true;
}

void onBluePress()
{
    Serial.println("Blue button pressed");
    Serial.println(CreateJson("Blue", GetLocalTime()));
    digitalWrite(LED_BLUE, HIGH);
    ledTimers[1] = millis();
    ledActives[1] = true;
}

void onGreenPress()
{
    Serial.println("Green button pressed");
    Serial.println(CreateJson("Green", GetLocalTime()));
    digitalWrite(LED_GREEN, HIGH);
    ledTimers[2] = millis();
    ledActives[2] = true;
}

void onYellowPress()
{
    Serial.println("Yellow button pressed");
    Serial.println(CreateJson("Yellow", GetLocalTime()));
    digitalWrite(LED_YELLOW, HIGH);
    ledTimers[3] = millis();
    ledActives[3] = true;
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // --- LED setup ---
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);

    // --- Button setup (use INPUT_PULLUP for active LOW buttons) ---
    pinMode(BUTTON_RED, INPUT);
    pinMode(BUTTON_BLUE, INPUT);
    pinMode(BUTTON_GREEN, INPUT);
    pinMode(BUTTON_YELLOW, INPUT);

    // --- Attach button handlers ---
    buttonRed.attachClick(onRedPress);
    buttonBlue.attachClick(onBluePress);
    buttonGreen.attachClick(onGreenPress);
    buttonYellow.attachClick(onYellowPress);

    // setup wifi and time
    TrySetupWifi();
    TrySetupTime();

    Serial.println("System Ready. Waiting for button presses...");
}

void loop()
{
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
}
