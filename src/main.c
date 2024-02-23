// main.c
#include "config.h"
#include <xc.h>
#include "system.h"
#include "buzzer.h"

int main(void) {
    SYSTEM_Initialize();
    BUZZER_Initialize();
    unsigned char test = OSCCON2bits.COSC;
    BUZZER_PlayC4();
    
    while (1) {
        
    }
    return 0;
}



