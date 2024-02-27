// uart.h
#ifndef UART_H
#define UART_H

#include <xc.h>
#include "system.h"

void UART_Initialize(void);

void UART_SendByte(unsigned char byte);

unsigned char UART_ReadByte(void);

#endif
