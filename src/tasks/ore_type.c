// ore_type.c
#include "ore_type.h"
#include "system.h"
#include "pcls.h"

#define ORE_TYPE_RED_ENABLE 1000
#define ORE_TYPE_YELLOW_ENABLE 2000
#define ORE_TYPE_BLUE_ENABLE 2000

#define ORE_TYPE_DEFAULT 0
#define ORE_TYPE_RED 1
#define ORE_TYPE_YELLOW 2
#define ORE_TYPE_BLUE 3

static unsigned char lastOreType;

void ORE_TYPE_Start(void) {
    PCLS_SetLaserScopeCommand(0x0001);
    lastOreType = ORE_TYPE_DEFAULT;
}

void ORE_TYPE_Run(void) {
    unsigned char oreType = ORE_TYPE_DetermineOreType();
    if (oreType != 0 && oreType != lastOreType) {
        PCLS_SetProcessingOreTypeCommand(oreType);
    }
    lastOreType = oreType;
}

void ORE_TYPE_End(void) {
    PCLS_SetLaserScopeCommand(0x0000);
    lastOreType = ORE_TYPE_DEFAULT;
}

int ORE_TYPE_IsEnabled(void) {
    return ORE_TYPE_DetermineOreType() != 0;
}

static unsigned char ORE_TYPE_DetermineOreType(void) {
    if (controller->leftJoystickX == ORE_TYPE_RED_ENABLE) {
        return ORE_TYPE_RED;
    } else if (controller->leftJoystickY == ORE_TYPE_YELLOW_ENABLE) {
        return ORE_TYPE_YELLOW;
    } else if (controller->leftJoystickX == ORE_TYPE_BLUE_ENABLE) {
        return ORE_TYPE_BLUE;
    }
    return 0;
}

Task oreTypeTask = {
    .start = ORE_TYPE_Start,
    .run = ORE_TYPE_Run,
    .end = ORE_TYPE_End,
    .isEnabled = ORE_TYPE_IsEnabled,
    .isRunning = 0
};
