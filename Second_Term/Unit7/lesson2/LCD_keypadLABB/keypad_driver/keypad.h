/*
 * keypad.h
 *
 * Created: 9/12/2023 3:15:07 AM
 *  Author: KH
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#define F_CPU 1000000UL

#include<avr/io.h>
#include<util/delay.h>

#define KEYPAD_PORT PORTD
#define Data_dir DDRD
#define keypadPIN PIND

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

void KEYPAD_INIT();
char KEYPAD_getchar();





#endif /* KEYPAD_H_ */