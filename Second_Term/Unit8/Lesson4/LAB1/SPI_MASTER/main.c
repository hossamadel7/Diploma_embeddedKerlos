/*
 * GccApplication3.c
 *
 * Created: 10/17/2023 5:48:15 PM
 * Author : KH
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>



#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7
void spiMASTER_init()
{
	DDRB |= (1<<MOSI) | (1<<SS) | (1<<SCK);
	
	DDRB &= ~(1<<MISO);
	
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<SPR0);
}

unsigned char SPI_MasterTransmit(unsigned char data)
{
	//Start transmission
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

int main(void)
{
    /* Replace with your application code */
	unsigned char ch =0;
	DDRA =0xFF;
	spiMASTER_init();
	_delay_ms(1000);
	for (ch=0;ch<=255 ;ch++)
	{
		_delay_ms(1000);
		PORTA=SPI_MasterTransmit(ch);
	}
}

