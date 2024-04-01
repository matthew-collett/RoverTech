// line_follower.c
#include "line_follower.h"
#include "system.h"

struct LineFollowerSensors sensors = {.left = 0, .middle = 0, .right = 0};

void LINE_FOLLOWER_Initialize(void) {
    
       
    // setting voltage reference
    ADREFbits.ADPREF = 0b00;
    ADREFbits.ADNREF = 0; //connected to Vss
    
    ADCON0bits.ADON = 1; // enable ADC conversion
    ADCON0bits.ADCS = 0; // setting conversion clock to FOSC/(2*(n+1)) 
    ADCLKbits.ADCCS = 0b111111; // using  FOSC /128
    ADCON0bits.ADFRM0 = 1; // setting results to be right-justified

    // ADCON0bits.ADGO = 1; This starts the conversion, need to set this to start
    
    ADCLKbits.ADCCS = 0b111111; // using  FOSC /128
    
    // ADC output
}


LineFollowerSensors LINE_FOLLOWER_ReadLineData(void) {
    // IF SOMETHING IS WRONG MAKE SURE LEFT RIGHT AND CENTER IS SET PROPERLY !!!!!!!!!!!!!!!!!
    unsigned int result;
    for (int i = 0; i < 3; i++) {
            // Select the ADC channel for the current sensor
        switch (i) {
            case 0:
                ADPCHbits.ADPCH = 0b001000; // Channel for sensor 1 (RB0)
                break;
            case 1:
                ADPCHbits.ADPCH = 0b001001; // Channel for sensor 2 (RB1 or RB2, check datasheet)
                break;
            case 2:
                ADPCHbits.ADPCH = 0b001010; // Channel for sensor 3 (RB3 or RB4, check datasheet)
                break;
        }  
        
        // refer to section 23.2.7 in PIC data sheet for example of basic mode
        ADCON0bits.ADON = 1; // Turn ADC on
        __delay_us(5);       // Wait for acquisition time (minimum TAD x 5, refer to datasheet for exact time)

        ADCON0bits.ADGO = 1; // Start ADC conversion
        while (ADCON0bits.ADGO); // Wait for conversion to complete

        // Read ADC result (right justified, ADRESH:ADRESL)
        result = ((unsigned int)ADRESH << 8) | ADRESL;
        if (i == 0) {
            sensors.left = result;
        } else if(i == 1) {
            sensors.middle = result;
        } else {
            sensors.right = result;
        } 
    }
    return sensors;
    __delay_ms(100);
}

void LINE_FOLLOWER_Stop(void) {
    ADCON0 = 0;
}
