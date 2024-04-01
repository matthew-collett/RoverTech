// trail_tracking.c
#include "trail_tracking.h"
#include "system.h"
#include "line_follower.h"
#include "motor_settings.h"
#include "pcls.h"

void TRAIL_TRACKING_Start(void) {
    LINE_FOLLOWER_Initialize();
}

void TRAIL_TRACKING_Run(void) {
    LineFollowerSensors sensors = LINE_FOLLOWER_ReadLineData(); // read line data
    int track = TRAIL_TRACKING_DetermineDirection(sensors); // determine direction to go
    PCLS_SetMotorSettingsCommand(MOTOR_SETTINGS_AutonomousSettings(track)); // send motor settings
}

void TRAIL_TRACKING_End(void) {
    MOTOR_SETTINGS_AutonomousSettings(TRACK_FINISHED);
    LINE_FOLLOWER_Stop();
}

int TRAIL_TRACKING_IsEnabled(void) {
    return controller->switchD == TRAIL_TRACKING_ENABLE;
}

int TRAIL_TRACKING_DetermineDirection(const LineFollowerSensors sensors) {
    // Case 1: Left sensor and right sensors are reading white and middle sensor is reading black. Drive forward
    if (sensors.left <= BLACK_THRESHOLD && 
        sensors.middle > BLACK_THRESHOLD && 
        sensors.right <= BLACK_THRESHOLD
    ) {
        return TRACK_FORWARD;
        
    // Case 2 : Left sensor and middle sensor are reading white and right sensor is reading black. Turn right
    } else if (
        sensors.left <= BLACK_THRESHOLD && 
        sensors.middle <= BLACK_THRESHOLD && 
        sensors.right > BLACK_THRESHOLD 
    ) {
        return TRACK_RIGHT;
        
    // Case 3 : Left sensor is reading white, middle sensor and right sensor are reading black. Turn right
    } else if (
        sensors.left <= BLACK_THRESHOLD && 
        sensors.middle > BLACK_THRESHOLD && 
        sensors.right > BLACK_THRESHOLD
    ) {
        return TRACK_RIGHT;
        
    // Case 4 : Left sensor is reading black, middle sensor and right sensor are reading white. Turn left
    } else if (
        sensors.left > BLACK_THRESHOLD && 
        sensors.middle <= BLACK_THRESHOLD && 
        sensors.right <= BLACK_THRESHOLD
    ) {
        return TRACK_LEFT;
        
    // Case 5 : Left sensor and middle sensor are reading black and right sensor is reading white. Turn left
    } else if (
        sensors.left > BLACK_THRESHOLD && 
        sensors.middle > BLACK_THRESHOLD && 
        sensors.right <= BLACK_THRESHOLD
    ) {
        return TRACK_LEFT;
    } else {
        return TRACK_FORWARD;
    }
}

Task trailTrackingTask = {
    .start = TRAIL_TRACKING_Start,
    .run = TRAIL_TRACKING_Run,
    .end = TRAIL_TRACKING_End,
    .isEnabled = TRAIL_TRACKING_IsEnabled,
    .isRunning = 0
};
