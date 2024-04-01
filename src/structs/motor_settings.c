// motor_settings.c
#include "motor_settings.h"
#include "system.h"
#include "trail_tracking.h"

#define JOYSTICK_DEADZONE 50
#define JOYSTICK_CENTER 1500
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD 2
#define MIN 1000
#define MAX 2000
#define AUTONOMOUS_SPEED 75
#define AUTONOMOUS_TURN_FACTOR 0.8

#define CALC_SPEED(pot) (((pot - MIN) * 100) / (MAX - MIN))

int MOTOR_SETTINGS_ComputeDeviation(const unsigned short joystick) {
    int deviation = (int) (joystick - JOYSTICK_CENTER); // calculate deviation
    if (abs(deviation) < JOYSTICK_DEADZONE) {
        return 0; // inside dead zone
    }
    // scale deviation to -100 to 100 range outside dead zone
    deviation = (deviation * 100) / (MAX - JOYSTICK_CENTER - JOYSTICK_DEADZONE);
    return deviation > 100 ? 100 : (deviation < -100 ? -100 : deviation);
}

MotorSettings* MOTOR_SETTINGS_MovementSettings(
    const unsigned short rightJoystickX,
    const unsigned short rightJoystickY,
    const unsigned short potentiometerA
) {
    MotorSettings* settings = controller->motorSettings;
    unsigned char baseSpeed = CALC_SPEED(potentiometerA);

    // compute deviation from center
    int yDeviation = MOTOR_SETTINGS_ComputeDeviation(rightJoystickY);
    int xDeviation = MOTOR_SETTINGS_ComputeDeviation(rightJoystickX);

    // set direction based on y deviation
    if(yDeviation != 0) {
        settings->motorADirection = MOTOR_SETTINGS_ResolveDirection(yDeviation);
        settings->motorBDirection = MOTOR_SETTINGS_ResolveDirection(yDeviation);
    }

    // adjust speeds for turning based on x deviation
    int aSpeedAdjustment = (xDeviation * baseSpeed) / 100;
    int bSpeedAdjustment = (-xDeviation * baseSpeed) / 100;

    // set motor speeds
    settings->motorASpeed = MOTOR_SETTINGS_ClampSpeed(baseSpeed + aSpeedAdjustment);
    settings->motorBSpeed = MOTOR_SETTINGS_ClampSpeed(baseSpeed + bSpeedAdjustment);
    return settings;
}

MotorSettings* MOTOR_SETTINGS_AutonomousSettings(const int track) {
    MotorSettings* settings = controller->motorSettings;;
    settings->motorADirection = DIRECTION_FORWARD;
    settings->motorASpeed = AUTONOMOUS_SPEED;
    settings-> motorBDirection = DIRECTION_FORWARD;
    settings->motorBSpeed = AUTONOMOUS_SPEED;
    switch (track) {
        case TRACK_RIGHT:
            // turn right
            settings->motorBSpeed = (unsigned char) (AUTONOMOUS_SPEED * AUTONOMOUS_TURN_FACTOR);
            break;
        case TRACK_LEFT:
            // turn left
            settings->motorASpeed = (unsigned char) (AUTONOMOUS_SPEED * AUTONOMOUS_TURN_FACTOR);
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

unsigned char MOTOR_SETTINGS_ResolveDirection(const int deviation) {
    return (unsigned char) deviation > 0 ? DIRECTION_FORWARD : DIRECTION_BACKWARD;
}

unsigned char MOTOR_SETTINGS_ClampSpeed(const int speed) {
    return (unsigned char) (speed > 100 ? 100 : (speed < 0 ? 0 : speed));
}