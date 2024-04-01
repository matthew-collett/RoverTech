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
    TRISCbits.TRISC4 = 1; // SCL line for I2C
    TRISCbits.TRISC3 = 1; // SDA line for I2C
    TRISBbits.TRISB0 = 1; // RB0 line follower sensor as input
    TRISBbits.TRISB1 = 1; // RB1 line follower sensor as input
    TRISBbits.TRISB2 = 1; // RB2 line follower sensor as input
    TRISCbits.TRISC6 = 1; // RC6 for UART RX as input
}

void PIN_MANAGER_OutputPins(void) {
    // OUTPUT PINS (TRISxbits.TRISxx = 0)
    TRISCbits.TRISC7 = 0; // RC7 for CCP PWM output
    TRISAbits.TRISA0 = 0; // RA0 for error LED as output
    TRISCbits.TRISC5 = 0; // RC5 UART TX output
}

void PIN_MANAGER_AnalogPins(void) {
    // ANALOG PINS (ANSELxbits.ANSxx = 1)
    ANSELBbits.ANSB0 = 1; // RB0 analog for line follower sensor
    ANSELBbits.ANSB1 = 1; // RB1 analog for line follower sensor
    ANSELBbits.ANSB2 = 1; // RB2 analog for line follower sensor
}

void PIN_MANAGER_DigitalPins(void) {    
    // DIGITAL PINS (ANSELxbits.ANSxx = 0)
    ANSELCbits.ANSC4 = 0; // SCL line for I2C
    ANSELCbits.ANSC3 = 0; // SDA line for I2C
    ANSELCbits.ANSC7 = 0; // RC7 for CCP PWM output as digital
    ANSELAbits.ANSA0 = 0; // RA0 for error LED as digital
    ANSELCbits.ANSC5 = 0; // RC5 as digital for UART TX
    ANSELCbits.ANSC6 = 0; // RC6 as digital for UART RX
}

void PIN_MANAGER_WeakPullUpResistors(void) {
    // WEAK PULL UP RESISTORS (WPxbits.WPUxx = 1)
}