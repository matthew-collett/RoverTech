// pcls.c
#include "pcls.h"
#include "system.h"
#include "uart.h"

#define SYNC_BYTE_1 0xFE
#define SYNC_BYTE_2 0x19
#define MSG_GET_USER_DATA_COMMAND 0x0501
#define MSG_GET_USER_DATA_RESPONSE 0x0502
#define MSG_SET_MOTOR_SETTINGS_COMMAND 0x0601
#define MSG_UNKNOWN_INVALID_ID 0x0003
#define PAYLOAD_SIZE_SET_MOTOR_SETTINGS_COMMAND 0x0004

void PCLS_GetUserDataCommand(void) {
    PCLS_StartMessage(MSG_GET_USER_DATA_COMMAND); // start message
    PCLS_SendPayloadSize(0x0000); // send payload size
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

void PCLS_StartMessage(const unsigned short messageId) {
    UART_SendByte(SYNC_BYTE_1); // send sync byte 1
    UART_SendByte(SYNC_BYTE_2); // send sync byte 2  
    UART_SendByte(messageId & 0xFF); // send LSB of message id
    UART_SendByte(messageId >> 8); // send MSB of message id
}

void PCLS_SendPayloadSize(const unsigned short payloadSize) {
    UART_SendByte(payloadSize & 0xFF); // send LSB of payload size
    UART_SendByte(payloadSize >> 8); // send MSB of payload size 
}

void PCLS_SyncCommunication(void) {
    while(UART_ReadByte() != SYNC_BYTE_1); // sync 1
    while(UART_ReadByte() != SYNC_BYTE_2); // sync 2
}

void PCLS_HandleUnexpectedMessageId(void) {
    PCLS_ReadShort(); // read payload size to clear the buffer
}

unsigned short PCLS_ReadShort(void) {
    unsigned char lsb = UART_ReadByte(); // read LSB of data
    unsigned char msb = UART_ReadByte(); // read MSB of data
    return ((unsigned short) msb << 8) | lsb; // concatenate into 2 bytes
}