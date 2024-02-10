// system.c
#include "system.h"
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "pps_manager.h"
#include "i2c.h"

void SYSTEM_Initialize() {
    // possibly something to do with the clock
    INTERRUPT_MANAGER_Initialize();
    PIN_MANAGER_Initialize();
    PPS_MANAGER_Initialize();
    I2C_Initialize();
}