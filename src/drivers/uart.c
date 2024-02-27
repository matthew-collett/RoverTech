// uart.c
#include "uart.h"

#define BAUD_RATE 9600

void UART_SetBaudRate(unsigned int baud_rate);

void UART_Initialize(void) {
    BAUD1CONbits.BRG16 = 1; // set 16-bit baud rate generator
	TX1STAbits.BRGH = 1; // enable high baud rate
    UART_SetBaudRate(BAUD_RATE) // set baud rate
    TX1STAbits.SYNC = 0; // enable asynchronous mode
    RC1STAbits.SPEN = 1; // enable serial transport
    TX1STAbits.TXEN = 1; // enable transmitter
    RCSTAbits.CREN = 1; // enable receiver
}

void UART_SendByte(unsigned char byte) {
    TXREG = byte; // send byte
    while(!PIR3bits.TXIF); // wait until transmission complete
}

unsigned char UART_ReadByte(void) {
    while (!PIR3bits.RCIF); // wait until data is received
    return RCREG; // read received data
}

void UART_SetBaudRate(unsigned int baud_rate) {
    unsigned int generator_value = (_XTAL_FREQ / (4 * BAUD_RATE)) - 1; // calculate generator value
    SPBRGL = generator_value & 0xFF; // load 8 LSB
    SPBRGH = (generator_value >> 8) & 0xFF; // load 8 MSB
}