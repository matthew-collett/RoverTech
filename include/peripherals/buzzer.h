// buzzer.h
#ifndef BUZZER_H
#define BUZZER_H

#include <xc.h>

void BUZZER_Initialize(void);

static void BUZZER_PlayNote(const float frequency);

void BUZZER_PlayC4(void);

void BUZZER_PlayF4(void);

void BUZZER_PlayA4(void);

void BUZZER_Stop(void);

static void BUZZER_SetDutyCycle(const unsigned short pr2);

#endif