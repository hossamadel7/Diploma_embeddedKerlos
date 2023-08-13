#include "state.h"
#include "DC_motor.h"

static int DC_speed=0;
void (*DC_state)();

void DC_Motor_Set(int speed)
{
	DC_speed = speed;
	printf("CA ---------------- speed = %d ---------------> DC Motor\n",DC_speed);

	DC_state = STATE(DC_busy);
}


void DC_init()
{
    //DC intializaion
    printf("============DC init=============\n");
}

STATE_define(DC_idle)
{

    DC_state_id = DC_idle;

	printf("DC Motor Idle State: speed = %d\n",DC_speed);

}

STATE_define(DC_busy)
{

	DC_state_id = DC_busy;

	printf("DC Motor Busy State: speed = %d\n",DC_speed);

	DC_state = STATE(DC_idle);

}