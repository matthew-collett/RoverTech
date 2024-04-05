// motor_settings.c
#include "motor_settings.h"
#include "system.h"
#include "trail_tracking.h"

#define JOYSTICK_DEADZONE 200
#define JOYSTICK_CENTER 1500
#define DIRECTION_BRAKE 0
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD 2
#define MIN_POT 1000
#define MAX_POT 2000
#define AUTONOMOUS_SPEED 75
#define TURN_FACTOR 2

#define CALC_SPEED(pot) ((pot - MIN_POT) / 10)
#define MAX(a, b) (a > b ? a : b)

MotorSettings* MOTOR_SETTINGS_MovementSettings(
    const unsigned short rightJoystickX,
    const unsigned short rightJoystickY,
    const unsigned short potentiometerA
) {
    MotorSettings* settings = controller->motorSettings;

    // Calculate speed from potentiometer value
    unsigned char speed = (unsigned char) CALC_SPEED(potentiometerA);

    // Determine the direction and turning
    if (rightJoystickY > JOYSTICK_CENTER + JOYSTICK_DEADZONE) {
        // Forward
        settings->motorADirection = DIRECTION_FORWARD;
        settings->motorBDirection = DIRECTION_FORWARD;
    } else if (rightJoystickY < JOYSTICK_CENTER - JOYSTICK_DEADZONE) {
        // Backward
        settings->motorADirection = DIRECTION_BACKWARD;
        settings->motorBDirection = DIRECTION_BACKWARD;
    } else {
        // Brake
        settings->motorADirection = DIRECTION_BRAKE;
        settings->motorBDirection = DIRECTION_BRAKE;
    }

    // Calculate turn based on right joystick X-axis
    int turnDifference = (int) rightJoystickX - JOYSTICK_CENTER;
    if (turnDifference > JOYSTICK_DEADZONE) {
        // Turning Right: Reduce speed of right motor
        settings->motorASpeed = (unsigned char) MAX(0, speed - abs(turnDifference / TURN_FACTOR));
        settings->motorBSpeed = speed;
    } else if (turnDifference < -JOYSTICK_DEADZONE) {
        // Turning Left: Reduce speed of left motor
        settings->motorASpeed = speed;
        settings->motorBSpeed = (unsigned char) MAX(0, speed - abs(turnDifference / TURN_FACTOR));
    } else {
        // Not turning
        settings->motorASpeed = speed;
        settings->motorBSpeed = speed;
    }

    return settings;
}

MotorSettings* MOTOR_SETTINGS_AutonomousSettings(const int track) {
    MotorSettings* settings = controller->motorSettings;
    settings->motorADirection = DIRECTION_FORWARD;
    settings->motorASpeed = AUTONOMOUS_SPEED;
    settings->motorBDirection = DIRECTION_FORWARD;
    settings->motorBSpeed = AUTONOMOUS_SPEED;
    switch (track) {
        case TRACK_RIGHT:
            // turn right
            settings->motorASpeed = 100;
            settings->motorBSpeed = 100;
            settings->motorASpeed = DIRECTION_BACKWARD;
            break;
        case TRACK_LEFT:
            // turn left
            settings->motorASpeed = 100;
            settings->motorBSpeed = 100;
            settings->motorBSpeed = DIRECTION_BACKWARD;
            break;
        case TRACK_FINISHED:
            // stop rover
            settings->motorASpeed = 0;
            settings->motorBSpeed = 0;
            break;
        default:
            break;
    }
    return settings;
}