// system.c
#include "system.h"
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "pps_manager.h"
#include "i2c.h"

void SYSTEM_Initialize() {
    /* Set Oscillator Source: HFINTOSC and Set Clock Divider: 1 */
    //OSCCON1bits.NOSC = 0x6;
    OSCFRQbits.HFFRQ = 0x2;
    TRISAbits.TRISA6 = 0;
    INTERRUPT_MANAGER_Initialize();
    PIN_MANAGER_Initialize();
    PPS_MANAGER_Initialize();
    I2C_Initialize();
}