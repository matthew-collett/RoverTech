// rgb_colours.h
#ifndef RGB_COLOURS_H
#define RGB_COLOURS_H

#include <xc.h>

#define COLOUR_RED 1
#define COLOUR_GREEN 2
#define COLOUR_BLUE 3

typedef struct RGBColours {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
    unsigned short clear;
} RGBColours;

RGBColours RGB_COLOURS_Normalize(const RGBColours rawColours);

int RGB_COLOURS_DetermineColour(const RGBColours colours);

#endif
