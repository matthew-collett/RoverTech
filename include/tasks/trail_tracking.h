// trail_tracking.h
#ifndef TRAIL_TRACKING_H
#define TRAIL_TRACKING_H

#include <xc.h>
#include "task.h"
#include "line_follower_sensors.h"

#define TRAIL_TRACKING_ENABLE 0x03E8
#define BLACK_THRESHOLD 0x0200
#define TRACK_START 0
#define TRACK_FORWARD 1
#define TRACK_RIGHT 2
#define TRACK_LEFT 3
#define TRACK_FINISHED 4

extern Task trailTrackingTask;

void TRAIL_TRACKING_Start(void);

void TRAIL_TRACKING_Run(void);

void TRAIL_TRACKING_End(void);

int TRAIL_TRACKING_IsEnabled(void);

static int TRAIL_TRACKING_DetermineDirection(const LineFollowerSensors sensors);

#endif