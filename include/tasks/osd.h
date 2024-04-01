// osd.h
#ifndef OSD_H
#define OSD_H

#include <xc.h>
#include "task.h"

extern Task osdTask;

void OSD_Start(void);

void OSD_Run(void);

void OSD_End(void);

int OSD_IsEnabled(void);

#endif