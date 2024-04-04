// osd.h
#ifndef ORE_TYPE_H
#define ORE_TYPE_H

#include <xc.h>
#include "task.h"

extern Task oreTypeTask;

void ORE_TYPE_Start(void);

void ORE_TYPE_Run(void);

void ORE_TYPE_End(void);

int ORE_TYPE_IsEnabled(void);

static unsigned char ORE_TYPE_DetermineOreType(void);

#endif