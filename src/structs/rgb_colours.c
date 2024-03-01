// rgb_colours.c
#include "rgb_colours.h"

RGBColours RGB_COLOURS_Initialize(void) {
    RGBColours colors;
    memset(&colors, 0, sizeof(colors));
    return colors;
}


