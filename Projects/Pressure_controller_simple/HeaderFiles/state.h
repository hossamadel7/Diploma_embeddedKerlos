#ifndef _state_H_
#define _state_H_ 

#include "driver.h"

#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE(_stateFUN_) ST_##_stateFUN_

void set_pressure(int p);
void alarmOn();
void alarmOff();
//void US_distance_set(int d);
//void DC_Motor_Set(int s);


#endif