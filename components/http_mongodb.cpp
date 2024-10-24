#include <HTTPClient.h>
#include "http_mongodb.h"

const char* serverUrl = "";

void send_data_to_mongodb(float temperature, float humidity, int light_level) {
    HTTPClient http;
    http.begin(serverUrl)
    htgtp.addHeader("Content-Type", "application/json");

    String payload = "{ \"temperature\": " + String(temperature) +
                     ", \"humidity\": " + String(humidity) +
                     ", \"light_level\": " + String(light_level) + " }";

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
        Serial.printf("Data sent to MongoDB, Response: %d\n", httpResponseCode);
    } else {
        Serial.printf("Failed to send data, Error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
}