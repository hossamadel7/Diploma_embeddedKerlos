/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *HossamPC
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f103x6.h"
#include "stm32_f103c6_GPIO.h"
#include "lcd.h"
#include "keypad.h"
#include "stm32_f103c6_EXTI.h"

int flag;

void clock_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();
}



void EXTI9_Callback(){
	flag=1;
	LCD_WRITE_STRING("IRQ9 has happened");
	my_wait_ms(1500);
	LCD_clear_screen();
}

int main(void)
{
	clock_init();
	LCD_INIT();
	KEYPAD_INIT();
	LCD_clear_screen();
	LCD_WRITE_STRING("Hello");
	my_wait_ms(1000);
	LCD_clear_screen();

	//initialize EXTI
	EXTI_PinConfig_t EXTI_pincfg;
	EXTI_pincfg.EXTI_pin=EXTI9_PB9;
	EXTI_pincfg.trigger_case=EXTI_Rising;
	EXTI_pincfg.IRQ_define = EXTI_IRQ_enable;
	EXTI_pincfg.P_IRQ_Callback = EXTI9_Callback;

	MCAL_EXTI_GPIO_Init(&EXTI_pincfg);

	while(1){
		if(flag){
			LCD_WRITE_STRING("CPUUUUUUU");
			my_wait_ms(1000);
			LCD_clear_screen();
			flag = 0;
		}
	}
}
