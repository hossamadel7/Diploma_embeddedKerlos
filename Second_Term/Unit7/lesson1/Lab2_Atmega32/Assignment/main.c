/*
 * unit7_Lesson1Ass.c
 *
 * Created: 9/7/2023 5:14:47 PM
 * Author : KH
 */ 
#define F_CPU 8000000ul
#include "meomMap.h"
#include "util/delay.h"
void wait(int x)
{
	int i;
	for (i = 0; i < x; ++i);
}

void GPIOD_init()
{
	SET_bit(DDRD,5);
	SET_bit(DDRD,6);
	SET_bit(DDRD,7);
	SET_bit(DDRD,4);
}


int main()
{
	GPIOD_init();
	while(1)
	{
		SET_bit(PORTD,5);
		_delay_ms(1000);
		RESET_bit(PORTD,5);

		SET_bit(PORTD,6);
		_delay_ms(1000);
		RESET_bit(PORTD,6);

		SET_bit(PORTD,7);
		_delay_ms(1000);
		RESET_bit(PORTD,7);
		_delay_ms(1000);
		SET_bit(PORTD,4);
		_delay_ms(1000);
		RESET_bit(PORTD,4);
		_delay_ms(1000);
	}

}


