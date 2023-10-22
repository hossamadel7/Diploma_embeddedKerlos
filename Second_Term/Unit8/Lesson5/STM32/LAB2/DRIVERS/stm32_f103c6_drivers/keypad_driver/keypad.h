/*
 * keypad.h
 *
 * Created: 9/12/2023 3:15:07 AM
 *  Author: KH
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "stm32_f103c6_GPIO.h"


#define KEYPAD_PORT GPIOB
#define Data_dir GPIOB


#define R0 GPIO_PIN0
#define R1 GPIO_PIN1
#define R2 GPIO_PIN3
#define R3 GPIO_PIN4
#define C0 GPIO_PIN5
#define C1 GPIO_PIN6
#define C2 GPIO_PIN7
#define C3 GPIO_PIN8

void KEYPAD_INIT();
char KEYPAD_getchar();





#endif /* KEYPAD_H_ */
