#ifndef _ALARM_H_
#define _ALARM_H_
#include "state.h"
enum 
{
	AlarmOn,
    AlarmOff,
    al_waiting
}alarm_state_id;

void alarm_init();

STATE_define(AlarmOff);
STATE_define(AlarmOn);
STATE_define(al_waiting);

extern void (*alarm_state)();

#endif // _PS_H_
