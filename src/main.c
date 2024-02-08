/*
 * File:   main.c
 * Author: Matthew
 *
 * Created on February 7, 2024, 7:37 PM
 */


#include <xc.h>

#define _XTAL_FREQ 32000000  // system oscillator frequency
#define I2C_SCL_SPEED 200000 // I2C SCL clock speed
#define APDS9960_I2C_ADDR 0x39 // address of colour sensor

// Register addresses and constants for the APDS9960
#define APDS9960_ENABLE 0x80
#define APDS9960_ATIME  0x81
#define APDS9960_CONTROL 0x8F

// Enable register values
#define APDS9960_PON 0x01
#define APDS9960_AEN 0x02

// Integration time and gain settings
#define APDS9960_ATIME_100MS 0xDB // 103ms
#define APDS9960_AGAIN_4X    0x01 // 4x gain


// Define the register addresses for the color data
#define APDS9960_CDATAL    0x94 // Clear data low byte
#define APDS9960_CDATAH    0x95 // Clear data high byte
#define APDS9960_RDATAL    0x96 // Red data low byte
#define APDS9960_RDATAH    0x97 // Red data high byte
#define APDS9960_GDATAL    0x98 // Green data low byte
#define APDS9960_GDATAH    0x99 // Green data high byte
#define APDS9960_BDATAL    0x9A // Blue data low byte
#define APDS9960_BDATAH    0x9B // Blue data high byte
#define APDS9960_STATUS    0x93 // Status register

void init(void);
void Initialize_PORT(void);
void Unlock_PPS(void);
void Initialize_PPS(void);
void Initialize_I2C(void);
void Lock_PPS(void);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char byte);
void I2C_WriteRegister(unsigned char addr, unsigned char reg, unsigned char value);
unsigned char I2C_ReadByte(void);
unsigned char I2C_ReadRegister(unsigned char addr, unsigned char reg);
void Initialize_APDS9960(void);
void I2C_ReadColorData(unsigned int *red, unsigned int *green, unsigned int *blue, unsigned int *clear);

void main(void) {
    unsigned int red;
    unsigned int green; 
    unsigned int blue; 
    unsigned int clear;
    
    init();
    while (1) {
        I2C_ReadColorData(&red, &green, &blue, &clear);
    }
}

void init(void) {
    INTCONbits.GIE = 1; // Enable global interrupts
    INTCONbits.PEIE = 1; // Enable peripheral interrupts
    
    Initialize_PORT();
    Unlock_PPS();
    Initialize_PPS(); 
    Initialize_I2C();
    Lock_PPS();
    Initialize_APDS9960();
}

void Initialize_PORT(void) {
    // RB1, RB2 as digital
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB2 = 0;
}

void Unlock_PPS(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;  
}

void Initialize_PPS(void) {
    SSP1CLKPPS = 0x09; // input: SCL is on RB1
    SSP1DATPPS = 0x0A; // input: SDA is on RB2
    RB1PPS = 0x14;     // output: SCL is on RB1
    RB2PPS = 0x15;     // output: SDA is on RB2
}

void Initialize_I2C(void) {
    // I2C master mode
    SSP1CON1 = 0b00101000;
    SSP1ADD = (_XTAL_FREQ / (4 * I2C_SCL_SPEED)) - 1;
}

void Lock_PPS(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
}

void I2C_Wait(void) {
    while ((SSP1CON2 & 0x1F) || (SSP1STATbits.R_nW));
}

void I2C_Start(void) {
    SSP1CON2bits.SEN = 1; 
    while(SSP1CON2bits.SEN); 
}

void I2C_Stop(void) {
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN); 
}

void I2C_SendByte(unsigned char byte) {
    SSP1BUF = byte; // Send byte
    while(SSP1STATbits.BF); // Wait until the transmission is complete
    while(SSP1CON2bits.ACKSTAT); // Wait for acknowledgment
}

unsigned char I2C_ReadByte(void) {
    unsigned char receivedByte;
    SSP1CON2bits.RCEN = 1; // Enable reception
    while (!SSP1STATbits.BF); // Wait until buffer is full
    receivedByte = SSP1BUF; // Read the received byte
    
    // Prepare to send NACK to indicate we're not expecting more data
    SSP1CON2bits.ACKDT = 1; // 1 = NACK (Not Acknowledge)
    SSP1CON2bits.ACKEN = 1; // Start the ACK/NACK transmission
    
    // Wait for NACK to finish sending
    while (SSP1CON2bits.ACKEN);
    return receivedByte;
}

unsigned char I2C_ReadRegister(unsigned char addr, unsigned char reg) {
    unsigned char receivedByte = 0;

    I2C_Start(); // Start I2C communication

    // Send device address with write flag (0) to indicate writing (register address)
    I2C_SendByte((unsigned char) (addr << 1) | 0); // Shift the address and append write bit (0)

    // Send register address
    I2C_SendByte((unsigned char) reg);

    // Repeated Start to switch to read mode without releasing the bus
    I2C_Start(); // Alternatively, some MCUs have a specific Repeated Start function

    // Send device address with read flag (1) to indicate reading
    I2C_SendByte((unsigned char) (addr << 1) | 1); // Shift the address and append read bit (1)

    // Read the byte from the specified register
    receivedByte = I2C_ReadByte();

    // Issue a stop condition to release the bus
    I2C_Stop();

    return receivedByte;
}

void I2C_WriteRegister(unsigned char addr, unsigned char reg, unsigned char value) {
    I2C_Start(); // Start I2C communication
    I2C_SendByte((unsigned char) (addr << 1)); // Send device address with write command
    I2C_SendByte((unsigned char) reg); // Send register address
    I2C_SendByte((unsigned char) value); // Send value to write
    I2C_Stop(); // Stop I2C communication
}

void I2C_ReadColorData(unsigned int *red, unsigned int *green, unsigned int *blue, unsigned int *clear) {
    unsigned char status = I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_STATUS);
    if(status & 0x01) { // Check if color data is ready
        // Read each color value
        *clear = (unsigned int) (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_CDATAL) | (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_CDATAH) << 8));
        *red   = (unsigned int) (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_RDATAL) | (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_RDATAH) << 8));
        *green = (unsigned int) (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_GDATAL) | (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_GDATAH) << 8));
        *blue  = (unsigned int) (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_BDATAL) | (I2C_ReadRegister(APDS9960_I2C_ADDR, APDS9960_BDATAH) << 8));
    }
}


void Initialize_APDS9960(void) {
    // Power on the sensor and enable RGB color sensing
    I2C_WriteRegister(APDS9960_I2C_ADDR, APDS9960_ENABLE, APDS9960_PON);
    __delay_ms(10); // Short delay for power stabilization
    
    // Set both Power ON and RGB Color Sensing
    I2C_WriteRegister(APDS9960_I2C_ADDR, APDS9960_ENABLE, APDS9960_PON | APDS9960_AEN);
    
    // Set ADC integration time to 103 milli seconds for color sensing
    I2C_WriteRegister(APDS9960_I2C_ADDR, APDS9960_ATIME, APDS9960_ATIME_100MS);
    
    // Set RGBC gain to 4x
    I2C_WriteRegister(APDS9960_I2C_ADDR, APDS9960_CONTROL, APDS9960_AGAIN_4X);
}

