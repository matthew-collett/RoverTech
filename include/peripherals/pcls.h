// pcls.h
#ifndef PCLS_H
#define PCLS_H

#include <xc.h>
#include "motor_settings.h"

void PCLS_GetUserDataCommand(void);

void PCLS_GetUserDataResponse(void);

void PCLS_SetMotorSettingsCommand(const MotorSettings* settings);

void PCLS_StartMessage(const unsigned short messageId);

void PCLS_SendPayloadSize(const unsigned short payloadSize);

void PCLS_SyncCommunication(void);

void PCLS_HandleUnexpectedMessageId(void);

unsigned short PCLS_ReadShort(void);

#endif