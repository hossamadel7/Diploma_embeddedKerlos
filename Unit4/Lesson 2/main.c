#include "US.h"
#include "DC_motor.h"
#include "CollsionAvoidance.h"
#include "state.h"

void setup()
{
	US_init();
	DC_init();
	printf("\n");

		//Set state pointers
	US_state = STATE(US_busy);
	CA_state = STATE(CA_waiting);
	DC_state = STATE(DC_idle);
}

void main(){
    setup();
    int n=10;
    while (n--)
    {
        US_state();
        CA_state();
        DC_state();
    }
    
}