// i2c.c
#include "i2c.h"

#define I2C_SCL_SPEED 100000 // I2C clock speed

void I2C_Initialize(void) {
    SSP1CON1 = 0x28; // SSPEN enabled, I2C master mode
    SSP1ADD = (_XTAL_FREQ / (4 * I2C_SCL_SPEED)) - 1; // baud rate generator
}

void I2C_Start(void) {
    SSP1CON2bits.SEN = 1; // initiate start condition on SDA and SCL pins
    while(SSP1CON2bits.SEN); // wait until start condition is not idle
    PIR3bits.SSP1IF = 0; // clear SSP interrupt flag
}

void I2C_RepeatedStart(void) {
    SSP1CON2bits.RSEN = 1; // initiate repeated start condition on SDA and SCL pins
    while(SSP1CON2bits.RSEN); // wait until repeated start condition is not idle
    PIR3bits.SSP1IF = 0; // clear SSP interrupt flag
}

void I2C_Stop(void) {
    SSP1CON2bits.PEN = 1; // initiate stop condition on SDA and SCL pins
    while(SSP1CON2bits.PEN); // wait until stop condition is not idle
    PIR3bits.SSP1IF = 0; // clear SSP interrupt flag
}

void I2C_SendByte(unsigned char byte) {
    SSP1BUF = byte; // send byte
    while(!PIR3bits.SSP1IF); // wait until the transmission is complete
    PIR3bits.SSP1IF = 0; // clear SSP interrupt flag
    if (SSP1CON2bits.ACKSTAT) { // if NACK then stop and return
        I2C_Stop();
        return;
    }
}

unsigned char I2C_ReadByte(void) {
    unsigned char receivedByte;
    SSP1CON2bits.RCEN = 1; // enable receive mode
    while (!SSP1STATbits.BF); // wait until buffer is full
    receivedByte = SSP1BUF; // read the received byte
    SSP1CON2bits.ACKDT = 1; // send the ACK bit for acknowledgment
    SSP1CON2bits.ACKEN = 1; // start the ACK transmission
    while (SSP1CON2bits.ACKEN); // wait for ACK to finish sending
    return receivedByte;
}

unsigned char I2C_ReadRegister(unsigned char addr, unsigned char reg) {
    unsigned char byte = 0;
    I2C_Start(); // start I2C communication
    I2C_SendByte((unsigned char) (addr << 1)); // send device address with write command
    I2C_SendByte((unsigned char) reg); // send register address
    I2C_RepeatedStart(); // repeated start I2C communication after writing
    I2C_SendByte((unsigned char) ((addr << 1) | 1)); // send device address with read command
    byte = I2C_ReadByte(); // read byte
    I2C_Stop(); // stop I2C communication
    return byte;
}

void I2C_WriteRegister(unsigned char addr, unsigned char reg, unsigned char value) {
    I2C_Start(); // start I2C communication
    I2C_SendByte((unsigned char) (addr << 1)); // send device address with write command
    I2C_SendByte((unsigned char) reg); // send register address
    I2C_SendByte((unsigned char) value); // send value to write
    I2C_Stop(); // stop I2C communication
}
