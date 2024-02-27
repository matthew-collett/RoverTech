// rgb_colours.h
#ifndef RGBCOLOURS_H
#define RGBCOLOURS_H

#include <string.h>

typedef struct RGBColours {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int clear;
} RGBColours;

RGBColours RGB_COLOURS_Initialize(void);

#endif
