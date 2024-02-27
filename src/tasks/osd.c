// optical_signal_decoding.c
#include "osd.h"

#define COLOUR_RED 1
#define COLOUR_GREEN 2
#define COLOUR_BLUE 3

int lastDetectedColor = -1;

void OSD_StartTask(void) {
    RGB_SENSOR_Initialize();
    BUZZER_Initialize();
}

void OSD_PerformTask(void) {
    OSD_StartTask();
    RGBColours colours = OSD_NormalizeColours(RGB_SENSOR_ReadColours());
    int currentDetectedColor = OSD_DetermineColour(colours);
    if (currentDetectedColor != lastDetectedColor) {
        __delay_ms(1000);
        switch (currentDetectedColor) {
            case COLOUR_RED:
                BUZZER_PlayC4();
                break;
            case COLOUR_GREEN:
                BUZZER_PlayF4();
                break;
            case COLOUR_BLUE:
                BUZZER_PlayA4();
                break;
            default:
                BUZZER_Stop(); 
                break;
        }
        lastDetectedColor = currentDetectedColor; 
    }
}

void OSD_EndTask(void) {
    RGB_SENSOR_Sleep();
    BUZZER_Stop();
}

RGBColours OSD_NormalizeColours(RGBColours rawColours) {
    RGBColours normalizedColours = RGB_COLOURS_Initialize(); // initialize colours to 0
    if (rawColours.clear != 0) {
        normalizedColours.red = rawColours.red / rawColours.clear; // normalize red
        normalizedColours.green = rawColours.green / rawColours.clear; // normalize green
        normalizedColours.blue = rawColours.blue / rawColours.clear; // normalize blue
    }
    return normalizedColours; // return normalized colour struct
}

int OSD_DetermineColour(RGBColours colours) {
    if (colours.red > colours.green && colours.red > colours.blue) {
        return COLOUR_RED; // colour is red
    } else if (colours.green > colours.red && colours.green > colours.blue) {
        return COLOUR_GREEN; // colour is green
    } else {
        return COLOUR_BLUE; // colour is blue
    }
}
