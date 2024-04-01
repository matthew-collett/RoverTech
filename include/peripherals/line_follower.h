// LINE_FOLLOWER.h
#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <xc.h>
#include "line_follower_sensors.h"

void LINE_FOLLOWER_Initialize(void);

LineFollowerSensors LINE_FOLLOWER_ReadLineData(void);

void LINE_FOLLOWER_Stop(void);

#endif