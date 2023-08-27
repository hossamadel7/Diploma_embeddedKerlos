#ifndef _PS_H_
#define _PS_H_
#include "state.h"
enum 
{
	PS_reading,
    PS_waiting
}PS_state_id;

void PS_init();
STATE_define(PS_reading);
STATE_define(PS_waiting);

extern void (*PS_state)();

#endif // _PS_H_
