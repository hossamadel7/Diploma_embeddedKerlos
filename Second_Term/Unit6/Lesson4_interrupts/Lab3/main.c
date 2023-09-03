#define F_CPU 8000000ul
#include "util/delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define baseIO 0x20
#define MCUCR *(volatile uint32_t *) (baseIO + 0x35)
#define MCUCSR *(volatile uint32_t *) (baseIO + 0x34)
#define GICR *(volatile uint32_t *) (baseIO + 0x3B)
#define PORTD *(volatile uint32_t *) (baseIO + 0x12)
#define DDRD *(volatile uint32_t *) (baseIO + 0x11)

#define SET_bit(ADDRESS, BIT) ADDRESS |= (1<<BIT)
#define RESET_bit(ADDRESS, BIT) ADDRESS &= ~(1<<BIT)



int main()
{
	//MCUCR init for any logical interrupt
	SET_bit(MCUCR,0);
	RESET_bit(MCUCR,1);
	///////////

	//Enable GEnerral Interrupts
	SET_bit(GICR,6);
	///////////

	//pin5 as output in portD
	SET_bit(DDRD,5);
	sei();
	while(1)
	{
		RESET_bit(PORTD,5);
		_delay_ms(1000);

	}


}

ISR(INT0_vect){
	SET_bit(PORTD,5);
	_delay_ms(1000);
}