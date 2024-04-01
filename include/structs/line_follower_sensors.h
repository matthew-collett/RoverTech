// line_follower_sensors.h
#ifndef LINE_FOLLOWER_SENSORS_H
#define LINE_FOLLOWER_SENSORS_H

#include <xc.h>

typedef struct LineFollowerSensors {
    unsigned int left;
    unsigned int middle;
    unsigned int right;
} LineFollowerSensors;

#endif
