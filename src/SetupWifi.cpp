#include "SetupWifi.h"
#include "esp_sntp.h"

const char *ssid = "IoT_H3/4";
const char *password = "98806829";
bool ConnectedToWifi = false;

bool ConnectWiFi()
{
    // Start connecting
    WiFi.begin(ssid, password);
    esp_sntp_servermode_dhcp(1);

    // Wait until connected
    int maxAttempts = 30; // ~15 seconds (30 * 500ms)
    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected!");
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else
    {
        Serial.println("Failed to connect to WiFi.");
        return false;
    }
}

void TrySetupWifi()
{
    // Setup Wifi
    if (!ConnectedToWifi)
    {
        ConnectedToWifi = ConnectWiFi();
    }
}