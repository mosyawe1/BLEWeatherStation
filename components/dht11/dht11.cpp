#include <iostream>
#include "driver/gpio.h"
#include "esp_log.h"
#include "dht.h"

// Define the GPIO pin for the DHT11 sensor
#define DHT11_GPIO_PIN GPIO_NUM_4

static const char* TAG = "DHT11";

// Initialize the DHT11 sensor (optional)
void DHT11_Init() {
    ESP_LOGI(TAG, "DHT11 Sensor initialized on GPIO %d", DHT11_GPIO_PIN);
}

// Function to read temperature from DHT11 sensor (use float version)
float read_temperature() {
    float temperature = 0; // Declare temperature as float
    esp_err_t result = dht_read_float_data(DHT_TYPE_DHT11, DHT11_GPIO_PIN, nullptr, &temperature); // Pass float pointer
    if (result == ESP_OK) {
        // ESP_LOGI(TAG, "Temperature: %.1f°C", (double)temperature); // Cast to double for logging
        return temperature;
    } else {
        // ESP_LOGE(TAG, "Failed to read temperature from DHT11");
        return -1; // Indicating error
    }
}

// Function to read humidity from DHT11 sensor (use float version)
float read_humidity() {
    float humidity = 0; // Declare humidity as float
    esp_err_t result = dht_read_float_data(DHT_TYPE_DHT11, DHT11_GPIO_PIN, &humidity, nullptr); // Pass float pointer
    if (result == ESP_OK) {
        // ESP_LOGI(TAG, "Humidity: %.1f%%", (double)humidity); // Cast to double for logging
        return humidity;
    } else {
        // ESP_LOGE(TAG, "Failed to read humidity from DHT11, error code: %d", result);
        return -1; // Indicating error
    }
}
