// controller_state.c
#include "controller_state.h"
#include "system.h"

void CONTROLLER_STATE_Initialize(void) {
    // allocate memory for controller
    controller = (ControllerState*) malloc(sizeof(ControllerState)); 
    
    // allocate memory for motor settings
    controller->motorSettings = (MotorSettings*) malloc(sizeof(MotorSettings));
}

