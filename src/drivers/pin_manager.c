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
//    TRISCbits.TRISC4 = 1; // RC4 SCL line for I2C
//    TRISCbits.TRISC3 = 1; // RC3 SDA line for I2C
    
    TRISBbits.TRISB1 = 1; // SCL line for I2C
    TRISBbits.TRISB2 = 1; // SDA line for I2C
}

void PIN_MANAGER_OutputPins(void) {
    // OUTPUT PINS (TRISxbits.TRISxx = 0)
    TRISCbits.TRISC7 = 0; // RC7 for CCP PWM output
}

void PIN_MANAGER_AnalogPins(void) {
    // ANALOG PINS (ANSELxbits.ANSxx = 1)
}

void PIN_MANAGER_DigitalPins(void) {    
    // DIGITAL PINS (ANSELxbits.ANSxx = 0)
//    ANSELCbits.ANSC4 = 0;// RC4 SCL line for I2C
//    ANSELCbits.ANSC3 = 0; // RC3 SDA line for I2C
    
    
    ANSELBbits.ANSB1 = 0;// SCL line for I2C
    ANSELBbits.ANSB2 = 0; // SDA line for I2C
    
    ANSELCbits.ANSC7 = 0; // RC7 for CCP PWM output
}

void PIN_MANAGER_WeakPullUpResistors(void) {
    // WEAK PULL UP RESISTORS (WPxbits.WPUxx = 1)
}