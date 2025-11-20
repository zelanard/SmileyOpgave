#include "Setup.h"

// Button press handlers

// This method is called when the red button is pressed
void onRedPress();

// This method is called when the blue button is pressed
void onBluePress();

// This method is called when the green button is pressed
void onGreenPress();

// This method is called when the yellow button is pressed
void onYellowPress();

// Turns on the specified LED and updates its timer and activity status
void ledOn(int ledPin, int ledIndex);

// Publishes an MQTT message for the specified button action
void mqttButtonAction(const char *buttonName, const char *message);
