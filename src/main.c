// main.c
#include "config.h"
#include <xc.h>
#include "system.h"
#include "buzzer.h"

void main(void) {
    SYSTEM_Initialize();  
    BUZZER_Initialize();
    BUZZER_PlayC4();
    while (1) {}
}



