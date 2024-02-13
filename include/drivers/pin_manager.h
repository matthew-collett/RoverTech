// pin_manager.h
#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>

void PIN_MANAGER_Initialize(void);

void PIN_MANAGER_InputPins(void);

void PIN_MANAGER_OutputPins(void);

void PIN_MANAGER_AnalogPins(void);

void PIN_MANAGER_DigitalPins(void);

void PIN_MANAGER_WeakPullUpResistors(void);

#endif