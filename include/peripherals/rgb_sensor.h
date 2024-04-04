// rgb_sensor.h
#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include <xc.h>
#include "rgb_colours.h"

void RGB_SENSOR_Initialize(void);

RGBColours RGB_SENSOR_ReadColours(void);

static unsigned short RGB_SENSOR_ReadColourChannel(
    const unsigned char lowByteAddr, 
    const unsigned char highByteAddr
);

static unsigned char RGB_SENSOR_DataReady(void);

void RGB_SENSOR_Sleep(void);

#endif