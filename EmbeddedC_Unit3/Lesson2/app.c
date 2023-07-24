#include "uart.h"

unsigned char string_buff[100]="learn-in-depth:hossam";

void main(void)
{
	Uart_Send_string(string_buff);
}