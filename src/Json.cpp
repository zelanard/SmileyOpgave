#include "Json.h"

char *CreateJson(const char *buttonName, String timeStamp)
{
    JsonDocument doc;
    doc[timeStamp] = buttonName;
    static char jsonBuffer[200];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}