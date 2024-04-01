// uart.c
#include "uart.h"
#include "system.h"

#define BAUD_RATE 115200
#define SPBRG ((_XTAL_FREQ / (4 * BAUD_RATE)) - 1)

void UART_Initialize(void) {
    BAUD1CONbits.BRG16 = 1; // set 16-bit baud rate generator
	TX1STAbits.BRGH = 1; // enable high baud rate
    UART_SetBaudRate(); // set baud rate
    TX1STAbits.SYNC = 0; // enable asynchronous mode
    RC1STAbits.SPEN = 1; // enable serial transport
    TX1STAbits.TXEN = 1; // enable transmitter
    RCSTAbits.CREN = 1; // enable receiver
}

void UART_SendByte(const unsigned char byte) {
    TXREG = byte; // send byte
    while(!PIR3bits.TXIF); // wait until transmission complete
}

unsigned char UART_ReadByte(void) {
    while (!PIR3bits.RCIF); // wait until data is received
    return RCREG; // read received data
}

void UART_SetBaudRate(void) {
    const unsigned short spbrg = SPBRG; // baud rate generator
    SPBRGL = spbrg & 0xFF; // load 8 LSB
    SPBRGH = spbrg >> 8; // load 8 MSB
}