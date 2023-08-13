
#include "CollsionAvoidance.h"
#include "state.h"

static int CA_distance = 0;
static int CA_speed = 0;
static int CA_threshold = 50;


void (*CA_state)();

void US_distance_set(int d){

	CA_distance = d;
    (CA_distance <= CA_threshold)?(CA_state = STATE(CA_waiting) ):(CA_state = STATE(CA_driving));

}

STATE_define(CA_waiting){
	CA_state_id= CA_waiting;
	printf("CA Waiting State: distance = %d\t speed = %d\n",CA_distance ,CA_speed);

	CA_speed = 0;

	DC_Motor_Set(CA_speed);


}

STATE_define(CA_driving){
	CA_state_id = CA_driving;
	printf("CA Driving State: distance = %d\t speed = %d\n",CA_distance ,CA_speed);

	CA_speed = 30;

	DC_Motor_Set(CA_speed);

}