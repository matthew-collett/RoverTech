// task.c
#include "task.h"

void TASK_ScheduleTask(Task* task) {
    if (task->isEnabled()) { 
        if (!task->isRunning) {
            task->start();
            task->isRunning = 1;
        }
        task->run(); 
    } else if (task->isRunning) {
        task->end();
        task->isRunning = 0;
    }
}


