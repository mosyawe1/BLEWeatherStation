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
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"  // For esp_restart and esp_get_minimum_free_heap_size
#include "esp_log.h"     // For logging
#include "esp_err.h"     // For esp_err_t
#include "dht11.h"
#include "rgb_led.h"


extern "C" void app_main(void) {
    DHT11_Init();
    init_rgb_led();


    while (1) {
        float temperature = read_temperature();

        vTaskDelay(pdMS_TO_TICKS(2000));
        
        float humidity = read_humidity();

        // std::cout << "Temperature: " << temperature << " °C" << std::endl;
        // std::cout << "Humidity: " << humidity << " %" << std::endl;
        
        // Print the readings
        if (temperature != -1) {
            printf("Temperature: %.1f°C\n", temperature);
        }
        if (humidity != -1) {
            printf("Humidity: %.1f%%\n", humidity);
        }

        // Delay for 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));

        if (temperature < 15) {
            set_rgb_led_color(255, 0, 0);
        }
        else if (temperature > 15 && temperature < 30) {
            set_rgb_led_color(0, 255, 0);
        }
        else {
            set_rgb_led_color(0, 0, 255);
        }
    }
}

//     std::cout << "Hello Moses!" << std::endl;
    
//     /* Print chip information */
//     esp_chip_info_t chip_info;
//     uint32_t flash_size;
//     esp_chip_info(&chip_info);
//     std::cout << "This is " << CONFIG_IDF_TARGET << " chip with " << chip_info.cores << " CPU core(s), "
//               << ((chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "")
//               << ((chip_info.features & CHIP_FEATURE_BT) ? "BT" : "")
//               << ((chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "")
//               << ((chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "")
//               << ", ";

//     unsigned major_rev = chip_info.revision / 100;
//     unsigned minor_rev = chip_info.revision % 100;
//     std::cout << "silicon revision v" << major_rev << "." << minor_rev << ", ";

//     if (esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
//         std::cout << "Get flash size failed" << std::endl;
//         return;
//     }

//     std::cout << (flash_size / (uint32_t)(1024 * 1024)) << "MB "
//               << ((chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external") << " flash" << std::endl;

//     std::cout << "Minimum free heap size: " << esp_get_minimum_free_heap_size() << " bytes" << std::endl;

//     for (int i = 10; i >= 0; i--) {
//         std::cout << "Restarting in " << i << " seconds..." << std::endl;
//         vTaskDelay(1000 / portTICK_PERIOD_MS); // Ensure this is defined correctly
//     }
    
//     std::cout << "Restarting now." << std::endl;
//     fflush(stdout);
//     esp_restart(); // Ensure this is defined correctly
// }
