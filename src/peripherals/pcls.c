// pcls.c
#include "pcls.h"
#include "system.h"
#include "uart.h"

#define SYNC_BYTE_1 0xFE
#define SYNC_BYTE_2 0x19

#define MSG_GET_PCLS_INFO_COMMAND 0x0401
#define PAYLOAD_SIZE_GET_PCLS_INFO_COMMAND 0x0000

#define MSG_GET_PCLS_INFO_RESPONSE 0x0402

#define MSG_GET_USER_DATA_COMMAND 0x0501
#define PAYLOAD_SIZE_GET_USER_DATA_COMMAND 0x0000
#define MSG_GET_USER_DATA_RESPONSE 0x0502

#define MSG_SET_MOTOR_SETTINGS_COMMAND 0x0601
#define PAYLOAD_SIZE_SET_MOTOR_SETTINGS_COMMAND 0x0004

#define MSG_SET_PROCESSING_PLANT_ORE_TYPE_COMMAND 0x0A03
#define PAYLOAD_SIZE_SET_PROCESSING_PLANT_ORE_TYPE_COMMAND 0x0001

#define MSG_SET_LASER_SCOPE_COMMAND 0x0801
#define PAYLOAD_SIZE_SET_LASER_SCOPE_COMMAND 0x0001

#define MSG_SHOOT_LASER_COMMAND 0x0901
#define PAYLOAD_SIZE_SHOOT_LASER_COMMAND 0x0001

#define SHOOT_LASER_COMMAND_HIGH_CALIBER_SHOT 0x0002

#define MSG_UNKNOWN_INVALID_ID 0x0003

void PCLS_GetPCLSInfoCommand(void) {
    PCLS_StartMessage(MSG_GET_PCLS_INFO_COMMAND); // start message
    PCLS_SendPayloadSize(PAYLOAD_SIZE_GET_PCLS_INFO_COMMAND); // send payload size
}

void PCLS_GetPCLSInfoResponse(void) {
    PCLS_SyncCommunication(); // sync communication
    
    unsigned short messageId = PCLS_ReadShort(); // read message id
    if (messageId != MSG_GET_PCLS_INFO_RESPONSE) {
        PCLS_HandleUnexpectedMessageId(); // handle unexpected message
        return;
    }
    PCLS_ReadShort(); // read payload size
}

void PCLS_GetUserDataCommand(void) {
    PCLS_StartMessage(MSG_GET_USER_DATA_COMMAND); // start message
    PCLS_SendPayloadSize(PAYLOAD_SIZE_GET_USER_DATA_COMMAND); // send payload size
}

void PCLS_GetUserDataResponse(void) {
    PCLS_SyncCommunication(); // sync communication
    
    unsigned short messageId = PCLS_ReadShort(); // read message id
    if (messageId != MSG_GET_USER_DATA_RESPONSE) {
        PCLS_HandleUnexpectedMessageId(); // handle unexpected message
        return;
    }
    
    PCLS_ReadShort(); // read payload size
    unsigned short rightJoystickX = PCLS_ReadShort(); // read right joystick x
    unsigned short rightJoystickY = PCLS_ReadShort(); // read right joystick y
    controller->leftJoystickY = PCLS_ReadShort(); // read left joystick y
    controller->leftJoystickX = PCLS_ReadShort(); // read left joystick x
    controller->switchA = PCLS_ReadShort(); // read switch a
    controller->switchB = PCLS_ReadShort(); // read switch b
    controller->switchC = PCLS_ReadShort(); // read switch c
    controller->switchD = PCLS_ReadShort(); // read switch d
    unsigned short potentiometerA = PCLS_ReadShort(); // read potentiometer a
    controller->potentiometerB = PCLS_ReadShort(); // read potentiometer b
    controller->motorSettings = MOTOR_SETTINGS_MovementSettings(
        rightJoystickX, 
        rightJoystickY, 
        potentiometerA
    ); 
}

void PCLS_SetMotorSettingsCommand(const MotorSettings* settings) {
    PCLS_StartMessage(MSG_SET_MOTOR_SETTINGS_COMMAND); // start message
    PCLS_SendPayloadSize(PAYLOAD_SIZE_SET_MOTOR_SETTINGS_COMMAND); // send payload size
    UART_SendByte(settings->motorADirection); // set motor a direction
    UART_SendByte(settings->motorASpeed); // set motor a speed
    UART_SendByte(settings->motorBDirection); // set motor b direction
    UART_SendByte(settings->motorBSpeed); // set motor b speed
}

void PCLS_SetProcessingOreTypeCommand(const unsigned char oreType) {
    PCLS_StartMessage(MSG_SET_PROCESSING_PLANT_ORE_TYPE_COMMAND); // start message
    PCLS_SendPayloadSize(PAYLOAD_SIZE_SET_PROCESSING_PLANT_ORE_TYPE_COMMAND); // send payload size
    UART_SendByte(oreType); // send ore type
}

void PCLS_SetLaserScopeCommand(const unsigned char enable) {
    PCLS_StartMessage(MSG_SET_LASER_SCOPE_COMMAND); // start message
    PCLS_SendPayloadSize(PAYLOAD_SIZE_SET_LASER_SCOPE_COMMAND); // send payload size
    UART_SendByte(enable); // send enable
}

void PCLS_ShootLaserCommand(void) {
    PCLS_StartMessage(MSG_SHOOT_LASER_COMMAND); // start message
    PCLS_SendPayloadSize(PAYLOAD_SIZE_SHOOT_LASER_COMMAND); // send payload size
    UART_SendByte(SHOOT_LASER_COMMAND_HIGH_CALIBER_SHOT); // send enable
}

static void PCLS_StartMessage(const unsigned short messageId) {
    UART_SendByte(SYNC_BYTE_1); // send sync byte 1
    UART_SendByte(SYNC_BYTE_2); // send sync byte 2  
    UART_SendByte(messageId & 0xFF); // send LSB of message id
    UART_SendByte(messageId >> 8); // send MSB of message id
}

static void PCLS_SendPayloadSize(const unsigned short payloadSize) {
    UART_SendByte(payloadSize & 0xFF); // send LSB of payload size
    UART_SendByte(payloadSize >> 8); // send MSB of payload size 
}

static void PCLS_SyncCommunication(void) {
    while(UART_ReadByte() != SYNC_BYTE_1); // sync 1
    while(UART_ReadByte() != SYNC_BYTE_2); // sync 2
}

static void PCLS_HandleUnexpectedMessageId(void) {
    PCLS_ReadShort(); // read payload size to clear the buffer
}

static unsigned short PCLS_ReadShort(void) {
    unsigned char lsb = UART_ReadByte(); // read LSB of data
    unsigned char msb = UART_ReadByte(); // read MSB of data
    return ((unsigned short) msb << 8) | lsb; // concatenate into 2 bytes
}