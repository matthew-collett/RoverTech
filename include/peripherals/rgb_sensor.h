// rgb_sensor.h
#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include <xc.h>

typedef struct {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int clear;
} RGBColours;

void RGB_SENSOR_Initialize(void);

RGBColours RGB_SENSOR_ReadColours(void);

#endif