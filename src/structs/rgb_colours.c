// rgb_colours.c
#include "rgb_colours.h"

RGBColours RGB_COLOURS_Normalize(const RGBColours rawColours) {
    RGBColours normalizedColours = {0}; // initialize colours to 0
    if (rawColours.clear != 0) {
        normalizedColours.red = (unsigned short) (((float) rawColours.red / rawColours.clear) * 10); // normalize red
        normalizedColours.green = (unsigned short) (((float) rawColours.green / rawColours.clear) * 10); // normalize green
        normalizedColours.blue = (unsigned short) (((float) rawColours.blue / rawColours.clear) * 10); // normalize blue
    }
    return normalizedColours; // return normalized colour struct
}

int RGB_COLOURS_DetermineColour(const RGBColours colours) {
    if (colours.red > colours.green && colours.red > colours.blue) {
        return COLOUR_RED; // colour is red
    } else if (colours.green > colours.red && colours.green > colours.blue) {
        return COLOUR_GREEN; // colour is green
    } else {
        return COLOUR_BLUE; // colour is blue
    }
}