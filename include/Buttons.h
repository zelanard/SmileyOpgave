#include "Setup.h"

void onRedPress();
void onBluePress();
void onGreenPress();
void onYellowPress();
void ledOn(int ledPin, int ledIndex);
void mqttButtonAction(const char *buttonName, const char *message);
