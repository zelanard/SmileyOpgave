#include "Json.h"

char* CreateJson(const char* buttonName, const char* timeStamp)
{
    StaticJsonDocument<512> doc;   // <-- bump this a lot just to test
    JsonObject obj = doc.to<JsonObject>();
    obj[timeStamp] = buttonName;

    static char jsonBuffer[200];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}