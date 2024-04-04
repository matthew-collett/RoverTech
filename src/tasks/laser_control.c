// ore_type.c
#include "laser_control.h"
#include "system.h"
#include "pcls.h"

#define LASER_CONTROL_SHOOT_ENABLE 0x03E8
#define LASER_CONTROL_HEAL_ENABLE 0x05DC
#define LASER_CONTROL_SCOPE_ENABLE 0x0001
#define LASER_CONTROL_SCOPE_DISABLE 0x0000


void LASER_CONTROL_Start(void) {
    PCLS_SetLaserScopeCommand(LASER_CONTROL_SCOPE_ENABLE);
}

void LASER_CONTROL_Run(void) {
    static unsigned short lastSwitchValue;
    unsigned short currentSwitchValue = controller->switchC;

    if (currentSwitchValue != lastSwitchValue) {
        switch (currentSwitchValue) {
            case LASER_CONTROL_SHOOT_ENABLE:
                PCLS_ShootLaserCommand();
                break;
            case LASER_CONTROL_HEAL_ENABLE:
                break;
            default: 
                break;
        }
        lastSwitchValue = currentSwitchValue;
    }
}

void LASER_CONTROL_End(void) {
    PCLS_SetLaserScopeCommand(LASER_CONTROL_SCOPE_DISABLE);
}

int LASER_CONTROL_IsEnabled(void) {
    return controller->switchC == LASER_CONTROL_SHOOT_ENABLE || 
           controller->switchC == LASER_CONTROL_HEAL_ENABLE;
}


Task laserControlTask = {
    .start = LASER_CONTROL_Start,
    .run = LASER_CONTROL_Run,
    .end = LASER_CONTROL_End,
    .isEnabled = LASER_CONTROL_IsEnabled,
    .isRunning = 0
};
