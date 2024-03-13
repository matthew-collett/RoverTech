// main.c
#include "config.h"
#include <xc.h>
#include "system.h"
#include "uart.h"

void main(void) {
    SYSTEM_Initialize();  
    UART_Initialize();
    unsigned char byte = 0xFF;
    
    while (1) {
        UART_SendByte(byte);
    }
}



