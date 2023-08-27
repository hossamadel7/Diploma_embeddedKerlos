#include "algo.h"

#define threeshold 20

void (*algo_state)();

int pressure;

void set_pressure(int p)
{
    pressure=p;
}

STATE_define(High_pressure_detection)
{
    Algo_state_id=High_pressure_detection;

    if(pressure>threeshold)
    {
        alarmOn();
    }
    algo_state=STATE(High_pressure_detection);
}
