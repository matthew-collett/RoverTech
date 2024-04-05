// cpcls_info.h
#ifndef PCLS_INFO_H
#define PCLS_INFO_H

#include <xc.h>

typedef struct PCLSInfo {
    unsigned char teamId;
    unsigned char playerId;
    unsigned short health;
    unsigned char shieldFlag;
    unsigned char repairFlag;
} PCLSInfo;

void PCLS_INFO_Initialize(void);

#endif