// pin_manager.h
#ifndef PPS_MANAGER_H
#define PPS_MANAGER_H

#include <xc.h>


void PPS_MANAGER_Initialize(void);

void PPS_Input_Initialize(void);

void PPS_Output_Initialize(void);

void PPS_Lock(void);

void PPS_Unlock(void);

#endif