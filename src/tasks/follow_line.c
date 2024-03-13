/*
 * File:   follow_line.c
 * Author: Eric
 *
 * Created on March 13, 2024, 3:59 PM
 */


#include <xc.h>
#include "follow_line.h"

void FOLLOW_LINE_StartTask(void){
    LINE_FOLLOWER_Initialize();
}

void FOLLOW_LINE_PerformTask(void){
    struct LineFollowerSensors data = LineFollowerSensors LINE_FOLLOWER_FollowLine();
}

void FOLLOW_LINE_EndTask(void){
    ADCON0bits.ADON = 0;
}