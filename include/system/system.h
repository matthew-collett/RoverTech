// system.h
#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include "controller_state.h"
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "pps_manager.h"
#include "i2c.h"
#include "uart.h"
#include "pcls.h"
#include "task_manager.h"

#define _XTAL_FREQ 32000000  // internal oscillator frequency (Fosc)

extern ControllerState* controller; // global controller state variable

void SYSTEM_Initialize(void);

void SYSTEM_Run(void);

void SYSTEM_Terminate(void);

#endif