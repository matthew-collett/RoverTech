// pin_manager.c
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void) {
    Input_Pins_Initialize();
    Output_Pins_Initialize();
    Analog_Pins_Initialize();
    Digital_Pins_Initialize();
}

void Input_Pins_Initialize(void) {
    // INPUT PINS (TRISxbits.TRISxx = 1)
    TRISBbits.TRISB1 = 1; // SCL line for I2C
    TRISBbits.TRISB2 = 1; // SDA line for I2C
}

void Output_Pins_Initialize(void) {
    // OUTPUT PINS (TRISxbits.TRISxx = 0)
}

void Analog_Pins_Initialize(void) {
    // ANALOG PINS (ANSELxbits.ANSxx = 1)
}

void Digital_Pins_Initialize(void) {    
    // DIGITAL PINS (ANSELxbits.ANSxx = 0)
    ANSELBbits.ANSB1 = 0;// SCL line for I2C
    ANSELBbits.ANSB2 = 0; // SDA line for I2C
    
}