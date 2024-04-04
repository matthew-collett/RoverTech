// pin_manager.h
#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>

void PIN_MANAGER_Initialize(void);

static void PIN_MANAGER_InputPins(void);

static void PIN_MANAGER_OutputPins(void);

static void PIN_MANAGER_AnalogPins(void);

static void PIN_MANAGER_DigitalPins(void);

static void PIN_MANAGER_WeakPullUpResistors(void);

#endif