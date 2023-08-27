#ifndef _ALGO_H_
#define _ALGO_H_
#include "state.h"
enum 
{
	High_pressure_detection
}Algo_state_id;

STATE_define(High_pressure_detection);

extern void (*algo_state)();

#endif // _PS_H_