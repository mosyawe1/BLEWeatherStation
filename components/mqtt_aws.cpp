#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "mqtt_aws.h"

// AWS IoT Core settings
const char* aws_endpoint = "";

//Set up SSL/TLS client

WiFiClientSecure espClient;
PubSubClient client(espClient);

void mqtt_init() {
    // Set AWS IoT endpoint
    client.setServer(aws_endpoint, 8883);

    // Load certificates and private key
    espClient.setCACert(AWS_ROOT_CA);
    espClient.setCertificate(DEVICE_CERT);
    espClient.setPrivateKey(DEVICE_PRIVATE_KEY);

    // Connect to AWS IoT Core
    while (!client.connected()) {
        Serial.println("Connecting to AWS IoT Core...");
        if (client.connect("ESP32Client")) {
            Serial.println("Connected to AWS IoT Core");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void publish_sensor_data(float temperature, float humidity, int light_level) {
    if (client.connected()) {

        String payload = "{\"temperature\":" + String(temperature) +
                         ", \"humidity\":" + String(humidity) +
                         ", \"light_level\":" + String(light_level) + "}";
        client.publish("sensor/weather_data", payload.c_str());
    }
}