#include <wifi.h>
#include "wifi_setup.h"

const char* ssid = "";
const char* password = "";

void wifi_connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}