// buzzer.h
#ifndef BUZZER_H
#define BUZZER_H

#include <xc.h>
#include "system.h"

void BUZZER_Initialize(void);

void BUZZER_PlayNote(float frequency);

void BUZZER_PlayC4(void);

void BUZZER_PlayF4(void);

void BUZZER_PlayA4(void);

#endif