#include "Setup.h"

bool activeLow = false;
bool pullupActive = true;

// Create  a globalOneButton objects
OneButton buttonRed(BUTTON_RED, activeLow, pullupActive);
OneButton buttonBlue(BUTTON_BLUE, activeLow, pullupActive);
OneButton buttonGreen(BUTTON_GREEN, activeLow, pullupActive);
OneButton buttonYellow(BUTTON_YELLOW, activeLow, pullupActive);

unsigned long ledTimers[4] = {0, 0, 0, 0};
bool ledActives[4] = {false, false, false, false};

//
unsigned long lastActivity = 0;
