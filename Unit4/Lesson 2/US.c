#include "US.h"

void (*US_state)();

unsigned int distance;

int generate_random(int l,int r,int count){
    int i;
    for (i = 0; i < count; i++)
    {
        int rand_num=(rand() %(r-l+1)) +l;
        return rand_num;
    }
}

void US_init()
{
    //init US sensor
    printf("DC_init\n");
}
STATE_define(US_busy)
{
    US_state_id=US_busy;
    distance=generate_random(45,55,1);
    printf("US_Busy state : distance=%d \n",distance);
    
    US_distance_set(distance);
    US_state=STATE(US_busy);
}
