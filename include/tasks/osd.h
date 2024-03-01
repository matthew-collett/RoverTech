// optical_signal_decoding.h
#ifndef OSD_H
#define OSD_H

#include <xc.h>
#include "system.h"
#include "rgb_sensor.h"
#include "buzzer.h"
#include "rgb_colours.h"

void OSD_StartTask(void);

void OSD_PerformTask(void);

void OSD_EndTask(void);

RGBColours OSD_NormalizeColours(RGBColours rawColours);

int OSD_DetermineColour(RGBColours colours);

#endif