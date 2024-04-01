// controller_state.h
#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include <xc.h>
#include "motor_settings.h"

typedef struct ControllerState {
    MotorSettings* motorSettings;
    unsigned short leftJoystickX;
    unsigned short leftJoystickY;
    unsigned short switchA;
    unsigned short switchB;
    unsigned short switchC;
    unsigned short switchD;
    unsigned short potentiometerB;
} ControllerState;

void CONTROLLER_STATE_Initialize(void);

#endif