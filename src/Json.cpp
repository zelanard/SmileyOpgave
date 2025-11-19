#include <ArduinoJson.h>

char *CreateJson(const char *buttonName, String timeStamp)
{
    StaticJsonDocument<512> doc;

    // Correctly add keys and values
    doc["Button"] = buttonName;
    doc["Time"] = timeStamp;

    static char jsonBuffer[512];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
    return jsonBuffer;
}
