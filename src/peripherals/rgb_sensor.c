// rgb_sensor.c
#include "rgb_sensor.h"

#define RGB_I2C_ADDR 0x39 // address of rgb sensor
#define RGB_ENABLE   0x80 // ENABLE register
#define RGB_ATIME    0x81 // ATIME register
#define RGB_CONTROL  0x8F // CONTROL register
#define RGB_CLEARL   0x94 // clear data low byte
#define RGB_CLEARH   0x95 // clear data high byte
#define RGB_REDL     0x96 // red data low byte
#define RGB_REDH     0x97 // red data high byte
#define RGB_GREENL   0x98 // green data low byte
#define RGB_GREENH   0x99 // green data high byte
#define RGB_BLUEL    0x9A // blue data low byte
#define RGB_BLUEH    0x9B // blue data high byte
#define RGB_STATUS   0x93 // status register

void RGB_SENSOR_Initialize(void) {
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_ENABLE, 0x01); // power on sensor 
    __delay_ms(10); // short delay for power stabilization
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_ENABLE, 0x01 | 0x02); // enable rgb
    //I2C_WriteRegister(RGB_I2C_ADDR, RGB_ATIME, 0xDB); // set integration time
    //I2C_WriteRegister(RGB_I2C_ADDR, RGB_CONTROL, 0x01); // set gain
}

RGBColours RGB_SENSOR_ReadColours(void) {
    struct RGBColours colours = RGB_COLOURS_Initialize();
    if (RGB_SENSOR_DataReady()) {
        colours.clear = RGB_SENSOR_ReadColourChannel(RGB_CLEARL, RGB_CLEARH);
        colours.red = RGB_SENSOR_ReadColourChannel(RGB_REDL, RGB_REDH);
        colours.green = RGB_SENSOR_ReadColourChannel(RGB_GREENL, RGB_GREENH);
        colours.blue = RGB_SENSOR_ReadColourChannel(RGB_BLUEL, RGB_BLUEH);
    }
    return colours;
}

unsigned int RGB_SENSOR_ReadColourChannel(unsigned char lowByte, unsigned char highByte) {
    unsigned char lowByte = I2C_ReadRegister(RGB_I2C_ADDR, lowByte); // read low byte
    unsigned char highByte = I2C_ReadRegister(RGB_I2C_ADDR, highByte); // read high byte
    return ((unsigned int) highByte << 8) | lowByte; // concatenate low and high byte for colour
}

unsigned char RGB_SENSOR_DataReady(void) {
    unsigned char status = I2C_ReadRegister(RGB_I2C_ADDR, RGB_STATUS); // read status register value
    return status & 0x01; // check if AVALID bit is set
}

void RGB_SENSOR_Sleep(void) {
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_ENABLE, 0x00); // put sensor in sleep mode
    __delay_ms(10);
}
