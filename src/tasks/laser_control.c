// ore_type.c
#include "laser_control.h"
#include "system.h"
#include "pcls.h"
#include "buzzer.h"

#define LASER_CONTROL_SHOOT_ENABLE 0x07D0
#define LASER_CONTROL_REQUEST_REPAIR_ENABLE 0x03E8
#define LASER_CONTROL_TRANSMIT_REPAIR_ENABLE 0x03E8
#define LASER_CONTROL_DEFAULT 0x05DC
#define LASER_CONTROL_SCOPE_ENABLE 0x0001
#define LASER_CONTROL_SCOPE_DISABLE 0x0000

static unsigned short lastSwitchValue;

void LASER_CONTROL_Start(void) {
    lastSwitchValue = LASER_CONTROL_DEFAULT;
    PCLS_SetLaserScopeCommand(LASER_CONTROL_SCOPE_ENABLE);
}

void LASER_CONTROL_Run(void) {
    unsigned short currentSwitchValue = controller->switchC;
    if (currentSwitchValue != lastSwitchValue) {
        switch (currentSwitchValue) {
            case LASER_CONTROL_SHOOT_ENABLE:
                PCLS_ShootLaserCommand();
                break;
            case LASER_CONTROL_REQUEST_REPAIR_ENABLE:
                PCLS_RequestRepairCodeLaserCommand(); // request repair code
                PCLS_GetPCLSInfoCommand(); // request PCLS info
                PCLS_GetPCLSInfoResponse(); // get PCLS info
                if (pclsInfo->repairFlag) {
                    BUZZER_Initialize();
                    BUZZER_PlayC4();
                    __delay_ms(1000);
                    BUZZER_Stop();
                }
                break;
            default: 
                break;
        }
        
        if (controller->switchB == LASER_CONTROL_TRANSMIT_REPAIR_ENABLE) {
            currentSwitchValue = LASER_CONTROL_TRANSMIT_REPAIR_ENABLE;
            if (pclsInfo->repairFlag) {
                PCLS_TransmitRepairCodeLaserCommand();
            }
        }
        lastSwitchValue = currentSwitchValue;
    }
}

void LASER_CONTROL_End(void) {
    lastSwitchValue = LASER_CONTROL_DEFAULT;
    PCLS_SetLaserScopeCommand(LASER_CONTROL_SCOPE_DISABLE);
}

int LASER_CONTROL_IsEnabled(void) {
    return controller->switchC == LASER_CONTROL_SHOOT_ENABLE || 
           controller->switchC == LASER_CONTROL_REQUEST_REPAIR_ENABLE ||
           controller->switchB == LASER_CONTROL_TRANSMIT_REPAIR_ENABLE;
}

Task laserControlTask = {
    .start = LASER_CONTROL_Start,
    .run = LASER_CONTROL_Run,
    .end = LASER_CONTROL_End,
    .isEnabled = LASER_CONTROL_IsEnabled,
    .isRunning = 0
};
