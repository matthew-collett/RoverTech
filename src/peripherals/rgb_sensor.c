// rgb_sensor.c
#include "rgb_sensor.h"

#define RGB_I2C_ADDR 0x39 // address of rgb sensor
#define RGB_ENABLE   0x80 // ENABLE register
#define RGB_ATIME    0x82 // ATIME register
#define RGB_CONTROL  0x8F // CONTROL register
#define RGB_PON      0x01 // PON bit value (power on)
#define RGB_AEN      0x02 // AEN bit value (rgb enable)
#define RGB_ADC      0xDB // ALS ADC value (103ms integration time)
#define RGB_GAIN     0x01 // AEN value (4x gain)
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
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_ENABLE, RGB_PON); // power on sensor 
    __delay_ms(10); // short delay for power stabilization
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_ENABLE, RGB_AEN); // enable rgb
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_ATIME, RGB_ADC); // set integration time
    I2C_WriteRegister(RGB_I2C_ADDR, RGB_CONTROL, RGB_GAIN); // set gain
}

RGBColours RGB_SENSOR_ReadColors(void) {
    
}
