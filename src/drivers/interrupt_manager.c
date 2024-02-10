// interrupt_manager.c
#include "interrupt_manager.h"

void INTERRUPT_MANAGER_Initialize(void) {
    INTCONbits.GIE = 1; // enable global interrupts
    INTCONbits.PEIE = 1; // enable peripheral interrupts
}
