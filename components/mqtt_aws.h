#ifndef MQTT_AWS_H
#define MQTT_AWS_H

void mqtt_init();
void publish_sensor_data(float temperature, float, humidity, int light_level);

#endif