// rgb_colours.c
#include "rgb_colours.h"

RGBColours RGBColours_Initialize(void) {
    RGBColours colors;
    memset(&colors, 0, sizeof(colors));
    return colors;
}


