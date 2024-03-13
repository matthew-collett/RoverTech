// uart.c
#include "uart.h"

#define BAUD_RATE 9600

void UART_Initialize(void) {
    BAUD1CONbits.BRG16 = 1; // set 16-bit baud rate generator
	TX1STAbits.BRGH = 1; // enable high baud rate
    SPBRGL = 0x40; // load LSB of baud rate calculation
    SPBRGH = 0x03; // load MSB of baud rate calculation
    TX1STAbits.SYNC = 0; // enable asynchronous mode
    RC1STAbits.SPEN = 1; // enable serial transport
    TX1STAbits.TXEN = 1; // enable transmitter
    RCSTAbits.CREN = 1; // enable receiver
}

void UART_SendByte(unsigned char byte) {
    TX1REGbits.TX1REG = byte; // send byte
    while(!PIR3bits.TXIF); // wait until transmission complete
}

unsigned char UART_ReadByte(void) {
    while (!PIR3bits.RCIF); // wait until data is received
    return RCREG; // read received data
}