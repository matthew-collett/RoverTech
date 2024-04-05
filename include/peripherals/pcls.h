// pcls.h
#ifndef PCLS_H
#define PCLS_H

#include <xc.h>
#include "motor_settings.h"

void PCLS_GetPCLSInfoCommand(void);

void PCLS_GetPCLSInfoResponse(void);

void PCLS_GetUserDataCommand(void);

void PCLS_GetUserDataResponse(void);

void PCLS_SetMotorSettingsCommand(const MotorSettings* settings);

void PCLS_SetProcessingOreTypeCommand(const unsigned char oreType);

void PCLS_SetLaserScopeCommand(const unsigned char enable);

void PCLS_ShootLaserCommand(void);

void PCLS_RequestRepairCodeLaserCommand(void);

void PCLS_TransmitRepairCodeLaserCommand(void);

static void PCLS_StartMessage(const unsigned short messageId);

static void PCLS_SendPayloadSize(const unsigned short payloadSize);

static void PCLS_SyncCommunication(void);

static void PCLS_HandleUnexpectedMessageId(void);

static unsigned short PCLS_ReadShort(void);

#endif