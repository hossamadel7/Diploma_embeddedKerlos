#include "PressureSensor.h"
#define PullTimer 10000
static int p;
void (*PS_state)();
void PS_init()
{
    //initlization of pressure sensor
    PS_state=STATE(PS_reading);
}

STATE_define(PS_reading)
{
    PS_state_id=PS_reading;
    p=getPressureVal();
    set_pressure(p);
    PS_state=STATE(PS_waiting);
}

STATE_define(PS_waiting)
{
    //waiting the delay 
    PS_state_id=PS_waiting;
    Delay(PullTimer);
    PS_state=STATE(PS_reading);
    
}