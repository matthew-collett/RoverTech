// task_manager.c
#include "task_manager.h"
#include "task.h"
#include "osd.h"
#include "trail_tracking.h"
#include "ore_type.h"
#include "laser_control.h"

void TASK_MANAGER_ScheduleTasks(void) {
    TASK_ScheduleTask(&osdTask);
    TASK_ScheduleTask(&trailTrackingTask);
    TASK_ScheduleTask(&oreTypeTask);
    TASK_ScheduleTask(&laserControlTask);
}
