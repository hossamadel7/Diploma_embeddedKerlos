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
    KEYPAD_INIT();
    _delay_ms(50);
    unsigned char key_pressed;
    while(1){
	    key_pressed = KEYPAD_getchar();
	    switch(key_pressed){
		    case 'A':
		    break;
		    case '?':
		    LCD_clear_screen();
		    break;
		    default:
		    LCD_WRITE_CHAR(key_pressed);
		    break;
	    }
    }
}

