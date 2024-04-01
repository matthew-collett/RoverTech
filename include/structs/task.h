// task.h
#ifndef TASK_H
#define TASK_H

#include <xc.h>

typedef struct Task {
    void (*start) (void);
    void (*run) (void);
    void (*end) (void);
    int (*isEnabled) (void);
    int isRunning;
} Task;

void TASK_ScheduleTask(Task* task);

#endif
