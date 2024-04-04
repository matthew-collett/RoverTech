// pps_manager.h
#ifndef PPS_MANAGER_H
#define PPS_MANAGER_H

#include <xc.h>

void PPS_MANAGER_Initialize(void);

static void PPS_MANAGER_InputPins(void);

static void PPS_MANAGER_OutputPins(void);

static void PPS_MANAGER_Lock(void);

static void PPS_MANAGER_Unlock(void);

#endif