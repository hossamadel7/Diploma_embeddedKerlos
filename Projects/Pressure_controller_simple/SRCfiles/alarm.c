#include "alarm.h"
void (*alarm_state)();
static int alarm=0;
void alarm_init()
{
    alarm_state=STATE(al_waiting);
    Set_Alarm_actuator(1);
}

STATE_define(al_waiting)
{
    alarm_state_id=al_waiting;
    // if(alarm==1) alarm_state=STATE(AlarmOn);
    // else alarm_state=STATE(AlarmOff);
}

STATE_define(AlarmOn)
{
    alarm_state_id=AlarmOn;
    Set_Alarm_actuator(0);
    Delay(10000);
    alarm_state=STATE(AlarmOff);
}
STATE_define(AlarmOff)
{
    alarm_state_id=AlarmOff;
    Set_Alarm_actuator(1);
    alarm_state=STATE(al_waiting);
}

void alarmOn()
{
    alarm_state=STATE(AlarmOn);
}
void alarmOff()
{
    alarm_state=STATE(AlarmOff);
}