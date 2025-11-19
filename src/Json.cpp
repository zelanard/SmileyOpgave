#include "Json.h"

char* CreateJson(const char* buttonName, const char* timeStamp)
{
    StaticJsonDocument<200> doc;
    doc["Button Name"] = buttonName;
    doc["Time Stamp"] = timeStamp;

    static char jsonBuffer[200];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}