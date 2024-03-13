// LINE_FOLLOWER.h
#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <xc.h>
#include "system.h"
#include "line_follower_sensors.h"

void LINE_FOLLOWER_Initialize(void);

LineFollowerSensors LINE_FOLLOWER_FollowLine(void);

#endif