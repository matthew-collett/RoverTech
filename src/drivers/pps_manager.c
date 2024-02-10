// pps_manager.c
#include "pps_manager.h"


void PPS_MANAGER_Initialize(void) {
    PPS_Unlock();
    PPS_Input_Initialize();
    PPS_Output_Initialize();
    PPS_Lock();
}

void PPS_Input_Initialize(void) {
    // INPUT PPS SELECTION (xxxPPS = xxx)
    SSP1CLKPPS = 0x09; // SCL is on RB1
    SSP1DATPPS = 0x0A; // SDA is on RB2
}

void PPS_Output_Initialize(void) {
    // OUTPUT PPS SELECTION (RxyPPS = xxx)
    RB1PPS = 0x14;     // SCL is on RB1
    RB2PPS = 0x15;     // SDA is on RB2
}

void PPS_Lock(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
}

void PPS_Unlock(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;  
}
