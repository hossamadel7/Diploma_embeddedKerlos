/*
 * uart.c
 *
 * Created: 10/9/2023 12:49:30 PM
 *  Author: KH
 */ 
#include "uart.h"

void UART_Init(void)
{
	//baudrate
	UBRRL=51;
	//normal mode
	UCSRA &= ~(1<<U2X);
	//frame
	
	// no parity
	//8bit data by default
	
	//Enable
	UCSRB |= (1<<TXEN);
	UCSRB |= (1<<RXEN);
	
}

void UART_send(unsigned char data)
{
	while(!read_bit(UCSRA,UDRE));
	UDR =data;
}

unsigned UART_receive(void)
{
	while(!read_bit(UCSRA,RXC));
	return UDR;
}

void send_number(uint32_t num)
{
	uint8_t *p=&num;
	UART_send(p[0]);
	UART_send(p[1]);
	UART_send(p[2]);
	UART_send(p[3]);


}
uint32_t recieve_number()
{
	uint32_t num;
	uint8_t *p=&num;

	p[0]=UART_receive();
	p[1]=UART_receive();
	p[2]=UART_receive();
	p[3]=UART_receive();

	return num;


}