#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Json.h"

// WiFi credentials
const char *ssid = "IoT_H3/4_5G";
const char *password = "98806829";

// MQTT broker settings
const char *mqtt_server = "wilson.local";
const int mqtt_port = 1883;
const char *mqtt_topic = "esp32/tatiana_jonas/button";

const int LED_RED = 5;
const int LED_BLUE = 19;
const int LED_GREEN = 21;
const int LED_YELLOW = 23;

const int BUTTON_RED = 35;
const int BUTTON_BLUE = 34;
const int BUTTON_GREEN = 32;
const int BUTTON_YELLOW = 33;

void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);

    pinMode(BUTTON_RED, INPUT_PULLUP);
    pinMode(BUTTON_BLUE, INPUT_PULLUP);
    pinMode(BUTTON_GREEN, INPUT_PULLUP);
    pinMode(BUTTON_YELLOW, INPUT_PULLUP);

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
}

void loop()
{
}