// system.c
#include "system.h"

ControllerState* controller = NULL; // initialize global controller state

void SYSTEM_Initialize(void) {
    CONTROLLER_STATE_Initialize();
    INTERRUPT_MANAGER_Initialize();
    PIN_MANAGER_Initialize();
    PPS_MANAGER_Initialize();
    I2C_Initialize();
    UART_Initialize();
}

void SYSTEM_Run(void) {
    while (1) {
        PCLS_GetUserDataCommand(); // request controller state
        PCLS_GetUserDataResponse(); // get controller state
        PCLS_SetMotorSettingsCommand(controller->motorSettings); // send motor settings
        TASK_MANAGER_ScheduleTasks(); // schedule tasks
    }
}

void SYSTEM_Terminate(void) {
    if (controller->motorSettings != NULL) {
        free(controller->motorSettings);
        controller->motorSettings = NULL;
    }

    if (controller != NULL) {
        free(controller);
        controller = NULL;
    }
}
