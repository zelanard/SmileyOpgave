#include "mqtt.h"

static WiFiClientSecure espClient;
static PubSubClient mqttClient(espClient);
String user = "elev1";
String pass = "password";
bool MQTTIsSetup = false;

void TryConnectMQTT()
{
    if (ConnectedToWifi && TimeIsSetup)
    {
        MQTTIsSetup = mqtt_setup();
    }
}

bool mqtt_setup()
{
    espClient.setInsecure();
    // espClient.setCACert(MQTT_CA_CERT);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    return true;
}

void mqtt_loop()
{
    if (!mqttClient.connected())
    {
        mqtt_reconnect();
    }
    mqttClient.loop();
}

void mqtt_reconnect()
{
    while (!mqttClient.connected())
    {
        Serial.print("Connecting to MQTT over TLS...");

        String clientId = "ESP32-" + String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str(), user.c_str(), pass.c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" - retrying in 5 seconds");
            delay(5000);
        }
    }
}

bool mqtt_publish(const String &payload)
{
    if (!mqttClient.connected())
    {
        mqtt_reconnect();
    }
    return mqttClient.publish(MQTT_TOPIC, payload.c_str());
}
