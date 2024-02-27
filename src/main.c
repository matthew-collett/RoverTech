// main.c
#include "config.h"
#include <xc.h>
#include "system.h"
#include "osd.h"

void main(void) {
    SYSTEM_Initialize();    
    while (1) {
        TRISAbits.TRISA5 = 1;
        ANSELAbits.ANSA5 = 0;
        if (!PORTAbits.RA0) {
            OSD_PerformTask();
        } else {
            OSD_EndTask();
        }
    }
}



