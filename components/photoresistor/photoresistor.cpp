#include "photoresistor.h"
#include "esp_log.h"

static const char* TAG = "PhotoResistor";
static adc_channel_t adc_channel;

void init_photoresistor(adc_channel_t channel) {
    adc_channel = channel;
    
    // Configure the ADC width and attenuation (optional tuning for voltage levels)
    adc1_config_width(ADC_WIDTH_BIT_12); // Set the ADC width to 12 bits (values range from 0-4095)
    adc1_config_channel_atten(channel, ADC_ATTEN_DB_0); // Set the attenuation to 0dB (max input is ~1.1V)

    ESP_LOGI(TAG, "Photoresistor initialized on channel %d", channel);
}

int read_photoresistor() {
    // Read the ADC value (0 - 4095)
    int value = adc1_get_raw(adc_channel);

    // Log the photoresistor value
    ESP_LOGI(TAG, "Photoresistor value: %d", value);

    return value;
}