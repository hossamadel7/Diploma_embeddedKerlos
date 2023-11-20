/*
 * uart.h
 *
 * Created: 10/9/2023 12:49:56 PM
 *  Author: KH
 */ 


#ifndef UART_H_
#define UART_H_

#include<avr/io.h>
#include<util/delay.h>

#define F_CPU 1000000UL
#define read_bit(reg,bit) ((reg>>bit)&1)
#define set_bit(reg,bit) reg|=(1<<bit)
#define clear_bit(reg,bit) reg&=~(1<<bit)

void UART_Init(void);
void UART_send(unsigned char data);
unsigned UART_receive(void);



#endif /* UART_H_ */