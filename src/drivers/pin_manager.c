// pin_manager.c
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void) {
    PIN_MANAGER_InputPins();
    PIN_MANAGER_OutputPins();
    PIN_MANAGER_AnalogPins();
    PIN_MANAGER_DigitalPins();
    PIN_MANAGER_WeakPullUpResistors();
}

void PIN_MANAGER_InputPins(void) {
    // INPUT PINS (TRISxbits.TRISxx = 1)
    TRISBbits.TRISB1 = 1; // SCL line for I2C
    TRISBbits.TRISB2 = 1; // SDA line for I2C
}

void PIN_MANAGER_OutputPins(void) {
    // OUTPUT PINS (TRISxbits.TRISxx = 0)
}

void PIN_MANAGER_AnalogPins(void) {
    // ANALOG PINS (ANSELxbits.ANSxx = 1)
}

void PIN_MANAGER_DigitalPins(void) {    
    // DIGITAL PINS (ANSELxbits.ANSxx = 0)
    ANSELBbits.ANSB1 = 0;// SCL line for I2C
    ANSELBbits.ANSB2 = 0; // SDA line for I2C
}

void PIN_MANAGER_WeakPullUpResistors(void) {
    // WEAK PULL UP RESISTORS (WPxbits.WPUxx = 1)
}