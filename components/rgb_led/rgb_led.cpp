#include "rgb_led.h"
#include "driver/ledc.h"

#define RED_PIN GPIO_NUM_23
#define GREEN_PIN GPIO_NUM_22
#define BLUE_PIN GPIO_NUM_21


void init_rgb_led() {
    // Configure PWM for RGB LED
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&ledc_timer);

    // Set up channels for R, G, and B
    ledc_channel_config_t ledc_channel[3] = {
        {.gpio_num = RED_PIN, .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0},
        {.gpio_num = BLUE_PIN, .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0},
        {.gpio_num = GREEN_PIN, .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_2,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0}
    };

    for (int i = 0; i < 3; i++) {
        ledc_channel_config(&ledc_channel[i]);
    }
}

void set_rgb_led_color(uint8_t red, uint8_t green, uint8_t blue) {
    // Set PWM duty for RGB LED
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, red);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, green);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, blue);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    
}
