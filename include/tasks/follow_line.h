// optical_signal_decoding.h
#ifndef FOLLOW_LINE_H
#define FOLLOW_LINE_H

#include <xc.h>
#include "system.h"
#include "line_follower.h"
#include "line_follower_sensors.h"

void FOLLOW_LINE_StartTask(void);

void FOLLOW_LINE_PerformTask(void);

void FOLLOW_LINE_EndTask(void);

#endif