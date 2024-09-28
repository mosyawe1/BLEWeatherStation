#ifndef RGB_LED_H
#define RGB_LED_H

#include <stdint.h>

void init_rgb_led();
void set_rgb_led_color(uint8_t red, uint8_t green, uint8_t blue);

#endif