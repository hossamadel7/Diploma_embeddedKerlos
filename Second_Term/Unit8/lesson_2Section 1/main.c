/*
 * Unit7_lesson2Lab1.c
 *
 * Created: 9/11/2023 7:19:29 PM
 * Author : KH
 */ 

#include "lcd_driver/lcd.h"
#include "keypad_driver/keypad.h"

int main(void)
{
    LCD_INIT();
    UART_Init();
	
    _delay_ms(50);
	LCD_WRITE_STRING("UART TR");
	UART_send('H');
	UART_send('O');
	
    while(1){
	    LCD_GOTO_XY(2,0);
		char x;
		x=UART_receive();
		LCD_WRITE_CHAR(x);
	}
}
