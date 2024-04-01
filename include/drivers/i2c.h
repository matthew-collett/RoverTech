// i2c.h
#ifndef I2C_H
#define I2C_H

#include <xc.h>

void I2C_Start(void);

void I2C_RepeatedStart(void);

void I2C_Stop(void);

void I2C_SendByte(const unsigned char byte);

unsigned char I2C_ReadByte(void);

void I2C_Initialize(void);

unsigned char I2C_ReadRegister(
    const unsigned char addr, 
    const unsigned char reg
);

void I2C_WriteRegister(
    const unsigned char addr, 
    const unsigned char reg, 
    const unsigned char value
);

#endif
