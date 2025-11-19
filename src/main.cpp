#include <Arduino.h>
#include <WiFi.h>
#include <OneButton.h>
#include <PubSubClient.h>
#include "Json.h"

// WiFi credentials
const char *ssid = "IoT_H3/4_5G";
const char *password = "98806829";

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
OneButton buttonRed(BUTTON_RED, true);
OneButton buttonBlue(BUTTON_BLUE, true);
OneButton buttonGreen(BUTTON_GREEN, true);
OneButton buttonYellow(BUTTON_YELLOW, true);

void onRedPress() {
  Serial.println("🔴 Red button pressed");
  digitalWrite(LED_RED, HIGH);
}

void onBluePress() {
  Serial.println("🔵 Blue button pressed");
  digitalWrite(LED_BLUE, HIGH);
}

void onGreenPress() {
  Serial.println("🟢 Green button pressed");
  digitalWrite(LED_GREEN, HIGH);
}

void onYellowPress() {
  Serial.println("🟡 Yellow button pressed");
  digitalWrite(LED_YELLOW, HIGH);
}

void setup() {
  Serial.begin(115200);

  // LED setup
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  // Button setup
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  // Attach button click handlers
  buttonRed.attachClick(onRedPress);
  buttonBlue.attachClick(onBluePress);
  buttonGreen.attachClick(onGreenPress);
  buttonYellow.attachClick(onYellowPress);

  Serial.println("System Ready. Waiting for button presses...");
}

void loop() {
  buttonRed.tick();
  buttonBlue.tick();
  buttonGreen.tick();
  buttonYellow.tick();
}
