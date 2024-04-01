// task_manager.c
#include "task_manager.h"
#include "task.h"
#include "osd.h"
#include "trail_tracking.h"

static Task* tasks[] = { &osdTask, &trailTrackingTask };
static int taskCount = sizeof(tasks) / sizeof(tasks[0]); 

void TASK_MANAGER_ScheduleTasks(void) {
    for (int i = 0; i < taskCount; i++) {
        TASK_ScheduleTask(tasks[i]);
    }
}
