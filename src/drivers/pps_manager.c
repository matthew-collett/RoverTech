// pps_manager.c
#include "pps_manager.h"

void PPS_MANAGER_Initialize(void) {
    PPS_MANAGER_Unlock();
    PPS_MANAGER_InputPins();
    PPS_MANAGER_OutputPins();
    PPS_MANAGER_Lock();
}

void PPS_MANAGER_InputPins(void) {
    // INPUT PPS SELECTION (xxxPPS = xxx)
//    SSP1CLKPPS = 0x14; // RC4 is SCL input for I2C
//    SSP1DATPPS = 0x13; // RC3 is SDA input for I2C
    
}

void PPS_MANAGER_OutputPins(void) {
    // OUTPUT PPS SELECTION (RxyPPS = xxx)
//    RC4PPS = 0x14; // RC4 is SCL output for I2C
//    RC3PPS = 0x15; // RC3 is SDA output for I2C
    
    
    RC7PPS = 0x09; // RC7 is CCP PWM output
}

void PPS_MANAGER_Lock(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
}

void PPS_MANAGER_Unlock(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;  
}
