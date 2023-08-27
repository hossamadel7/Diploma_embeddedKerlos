
#include "state.h"
#include "alarm.h"
#include "algo.h"
#include "PressureSensor.h"


void setup(){
	GPIO_INITIALIZATION();
    alarm_init();
	PS_init();
    algo_state=STATE(High_pressure_detection);
}
void main(){
	setup();
	while (1)
	{
		alarm_state();
		PS_state();
        algo_state();
        alarm_state();
	}

}