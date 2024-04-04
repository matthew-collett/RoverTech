// motor_settings.h
#ifndef MOTOR_SETTINGS_H
#define MOTOR_SETTINGS_H

#include <xc.h>

typedef struct MotorSettings {
    unsigned char motorADirection;
    unsigned char motorASpeed;
    unsigned char motorBDirection;
    unsigned char motorBSpeed;
} MotorSettings;

MotorSettings* MOTOR_SETTINGS_MovementSettings(
    const unsigned short rightJoystickX,
    const unsigned short rightJoystickY,
    const unsigned short potentiometerA
);

MotorSettings* MOTOR_SETTINGS_AutonomousSettings(const int track);

static int MOTOR_SETTINGS_ComputeDeviation(const unsigned short joystick);

static unsigned char MOTOR_SETTINGS_ResolveDirection(const int deviation);

static unsigned char MOTOR_SETTINGS_ClampSpeed(const int speed);

#endif