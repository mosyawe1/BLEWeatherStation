/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <iostream>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht11.h"
#include "rgb_led.h"
#include "photoresistor.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"  // For esp_restart and esp_get_minimum_free_heap_size
#include "esp_log.h"     // For logging
#include "esp_err.h"     // For esp_err_t


// Define pins and channels
#define PHOTORESISTOR_ADC_CHANNEL ADC1_CHANNEL_6  // GPIO34

// Task to read the temperature and humidity
void temperature_humidity_task(void *pvParameters) {
    while (1) {
        float temperature = read_temperature();
        float humidity = read_humidity();

        // Print the readings
        if (temperature != -1) {
            printf("Temperature: %.1f°C\n", temperature);
        }
        if (humidity != -1) {
            printf("Humidity: %.1f%%\n", humidity);
        }

        // Delay for 2 seconds before next reading
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task to read the photoresistor and control the RGB LED
void light_control_task(void *pvParameters) {
    while (1) {
        // Read the photoresistor value
        int light_level = read_photoresistor();

        // Adjust RGB LED based on light level
        if (light_level < 1000) {
            set_rgb_led_color(255, 0, 0); // Dim light, red LED
        } else if (light_level >= 1000 && light_level < 3000) {
            set_rgb_led_color(0, 255, 0); // Medium light, green LED
        } else {
            set_rgb_led_color(0, 0, 255); // Bright light, blue LED
        }

        // Delay for 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task to control RGB LED based on temperature
void temperature_led_task(void *pvParameters) {
    while (1) {
        float temperature = read_temperature();

        // Adjust RGB LED color based on temperature
        if (temperature < 15) {
            set_rgb_led_color(255, 0, 0); // Cold temperature, red LED
        } else if (temperature >= 15 && temperature < 30) {
            set_rgb_led_color(0, 255, 0); // Normal temperature, green LED
        } else {
            set_rgb_led_color(0, 0, 255); // Hot temperature, blue LED
        }

        // Delay for 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Main entry point
extern "C" void app_main(void) {
    // Initialize the sensors and RGB LED
    DHT11_Init();
    init_rgb_led();
    init_photo_resistor(PHOTORESISTOR_ADC_CHANNEL);

    // Create tasks for temperature/humidity, light control, and temperature-based LED
    xTaskCreate(temperature_humidity_task, "TemperatureHumidityTask", 2048, NULL, 1, NULL);
    xTaskCreate(light_control_task, "LightControlTask", 2048, NULL, 1, NULL);
    xTaskCreate(temperature_led_task, "TemperatureLEDTask", 2048, NULL, 1, NULL);

    // Let FreeRTOS handle task scheduling
}
