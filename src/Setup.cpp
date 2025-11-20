#include "Setup.h"

// Define if buttons are active LOW with internal pull-up resistors
bool activeLow = false;

// Use internal pull-up resistors
bool pullupActive = true;

// Create  a globalOneButton objects
OneButton buttonRed(BUTTON_RED, activeLow, pullupActive);
OneButton buttonBlue(BUTTON_BLUE, activeLow, pullupActive);
OneButton buttonGreen(BUTTON_GREEN, activeLow, pullupActive);
OneButton buttonYellow(BUTTON_YELLOW, activeLow, pullupActive);

// LED management
unsigned long ledTimers[4] = {0, 0, 0, 0};

// LED activity status
bool ledActives[4] = {false, false, false, false};

// Last activity timestamp
unsigned long lastActivity = 0;
