#ifndef _state_H_
#define _state_H_ 

#include <stdio.h>
#include <stdlib.h>

#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE(_stateFUN_) ST_##_stateFUN_

void US_distance_set(int d);
void DC_Motor_Set(int s);


#endif