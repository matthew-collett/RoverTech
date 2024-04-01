// main.c
#include "config.h"
#include "system.h"

int main(void) {
    SYSTEM_Initialize(); 
    SYSTEM_Run();
    SYSTEM_Terminate();
    return 0;
}



