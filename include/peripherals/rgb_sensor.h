// rgb_sensor.h
#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include <xc.h>
#include "i2c.h"

typedef struct RGBColours {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int clear;
} RGBColours;

void RGB_SENSOR_Initialize(void);

RGBColours RGB_SENSOR_ReadColours(void);

unsigned int RGB_SENSOR_ReadColourChannel(unsigned char lowByteAddr, unsigned char highByteAddr);

unsigned char RGB_SENSOR_DataReady(void);

unsigned char RGB_SENSOR_ReadDeviceId(void);

#endif