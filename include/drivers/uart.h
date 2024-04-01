// uart.h
#ifndef UART_H
#define UART_H

#include <xc.h>

void UART_Initialize(void);

void UART_SendByte(const unsigned char byte);

unsigned char UART_ReadByte(void);

void UART_SetBaudRate(void);

#endif
