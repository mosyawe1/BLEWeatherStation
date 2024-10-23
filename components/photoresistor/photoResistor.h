#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include "driver/adc.h"

// Initialize the photoresistor
void init_photoresistor(adc1_channel_t channel);

// Read the photoresistor value
int read_photoresistor();

#endif // PHOTORESISTOR_H
