// osd.c
#include "osd.h"
#include "system.h"
#include "task.h"
#include "rgb_sensor.h"
#include "rgb_colours.h"
#include "buzzer.h"

#define OSD_ENABLE 0x03E8

void OSD_Start(void) {
    RGB_SENSOR_Initialize();
    BUZZER_Initialize();
}

void OSD_Run(void) {
    RGBColours colours = RGB_COLOURS_Normalize(RGB_SENSOR_ReadColours());
    int detectedColour = RGB_COLOURS_DetermineColour(colours);
    switch (detectedColour) {
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
}

void OSD_End(void) {
    RGB_SENSOR_Sleep();
    BUZZER_Stop();
}

int OSD_IsEnabled(void) {
    return controller->switchD == OSD_ENABLE;
}

Task osdTask = {
    .start = OSD_Start,
    .run = OSD_Run,
    .end = OSD_End,
    .isEnabled = OSD_IsEnabled,
    .isRunning = 0
};
