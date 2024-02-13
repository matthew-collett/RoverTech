// i2c.h
#ifndef I2C_H
#define I2C_H

#include <xc.h>

#define _XTAL_FREQ 32000000  // system oscillator frequency (Fosc)

void I2C_Initialize(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char byte);
unsigned char I2C_ReadByte(void);
unsigned char I2C_ReadRegister(unsigned char addr, unsigned char reg);
void I2C_WriteRegister(unsigned char addr, unsigned char reg, unsigned char value);

#endif
