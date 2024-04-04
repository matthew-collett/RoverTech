// laser_control.h
#ifndef LASER_CONTROL_H
#define LASER_CONTROL_H

#include <xc.h>
#include "task.h"

extern Task laserControlTask;

void LASER_CONTROL_Start(void);

void LASER_CONTROL_Run(void);

void LASER_CONTROL_End(void);

int LASER_CONTROL_IsEnabled(void);

#endif