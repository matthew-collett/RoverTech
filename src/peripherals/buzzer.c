// buzzer.c
#include "buzzer.h"

#define C4_FREQ 261.63 // frequency for C4 note
#define F4_FREQ 349 // frequency for F4 note
#define A4_FREQ 440 // frequency for A4 note

void BUZZER_Initialize(void) {    
    // PR2
    PR2 = ((_XTAL_FREQ / (C4_FREQ * 4 * 16)) - 1);
    
    // CCP & PWM
    CCP1CON = 0x8F;
    CCPTMRS0 = 0x01; // This sets the C1TSEL bits to 01 to select Timer2 for CCP1

    
    // duty cycle
    unsigned int dutyCycle = (unsigned int) (0.5 * 4 * (PR2 + 1));
    CCPR1L = dutyCycle & 0xFF;
    CCPR1H = (dutyCycle >> 8) & 0x03;
    
    // Timer2
    PIR4bits.TMR2IF = 0; // clear interrupt
	T2CLKCON = 0x01; // set Timer2 to Fosc/4
    T2CON = 0xC0;
    T2HLT = 0x80;
    
    // wait for interrupt
    while(!PIR4bits.TMR2IF);
    TRISCbits.TRISC7 = 0;
}

void BUZZER_PlayNote(float frequency) {

}

void BUZZER_PlayC4(void) {
    BUZZER_PlayNote(C4_FREQ);
}

void BUZZER_PlayF4(void) {
    BUZZER_PlayNote(F4_FREQ);
}

void BUZZER_PlayA4(void) {
    BUZZER_PlayNote(A4_FREQ);
}
