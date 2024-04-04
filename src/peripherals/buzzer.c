// buzzer.c
#include "buzzer.h"
#include "system.h"

#define C4_FREQ 261.63
#define F4_FREQ 349.23 
#define A4_FREQ 440.0 

#define DUTY_CYCLE(pr2) (0.5 * 4 * (pr2 + 1))
#define PWM_FREQUENCY(frequency) ((_XTAL_FREQ / (frequency * 4 * 128)) - 1)

void BUZZER_Initialize(void) {    
    CCP1CON = 0x8F; // enable CCP and set to PWM Mode
    CCPTMRS0 = 0x01; // select Timer2 for CCP
    PIR4bits.TMR2IF = 0; // clear Timer2 interrupt
	T2CLKCON = 0x01; // set Timer2 clock source to Fosc/4
    T2CON = 0xF0; // enable Timer2 and set 1:128 pre-scaler
    while(!PIR4bits.TMR2IF); // wait for Timer2 interrupt
}

static void BUZZER_PlayNote(const float frequency) {
    PR2 = (unsigned char) PWM_FREQUENCY(frequency); // load PR2 with PWM frequency
    BUZZER_SetDutyCycle(PR2); // set duty cycle to 50%
}

void BUZZER_PlayC4(void) {
    BUZZER_PlayNote(C4_FREQ); // play c4
}

void BUZZER_PlayF4(void) {
    BUZZER_PlayNote(F4_FREQ); //play f4
}

void BUZZER_PlayA4(void) {
    BUZZER_PlayNote(A4_FREQ); // play a4
}

void BUZZER_Stop(void) {
    BUZZER_SetDutyCycle(0); // set duty cycle to 0% to stop tone
    CCP1CON = 0x00; // disable CCP1 module
    T2CON = 0x00; // disable Timer2
}

static void BUZZER_SetDutyCycle(const unsigned short pr2) {
    unsigned short dutyCycle = (unsigned short) DUTY_CYCLE(pr2); // calculate duty cycle
    CCPR1L = dutyCycle & 0xFF; // load 8 LSB of duty cycle
    CCPR1H = (dutyCycle >> 8) & 0x03; // load 2 MSB of duty cycle
}
