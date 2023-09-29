/*
 * stm32_f103c6_GPIO.c
 *
 *  Created on: Sep 13, 2023
 *      Author: KH
 */


#include "stm32_f103c6_EXTI.h"
#include "stm32_f103c6_GPIO.h"

void (*Gp_IRQ_Callback[15])(void);


// macrooooo

#define AFIO_EXTI_GPIO_MAPPING(x)                   ((x==GPIOA)? 0:\
												    (x==GPIOB)? 1:\
													(x==GPIOC)?2:\
													(x==GPIOD)?3:0 )


//=====================================

void EXTI_UPDATE(EXTI_PinConfig_t* EXTI_config){
	//1-configure GPIO pin to be Alternative(floating)

	GPIO_PinConfig_t pincfg;
	pincfg.GPIO_PinNumber = EXTI_config->EXTI_pin.GPIO_pin_number;
	pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
	MCAL_GPIO_Init(EXTI_config->EXTI_pin.GPIO_port, &pincfg);

	//============================================================================================
	//2- update AFIO to route between EXTI line with port A,B,C,D
	uint8_t AFIO_EXTICR_index = EXTI_config->EXTI_pin.EXTI_line_number / 4;
	uint8_t AFIO_EXTICR_position = (EXTI_config->EXTI_pin.EXTI_line_number % 4)*4;

	//clear the 4 bits of the AFIO_EXTICR first before writing
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_position);

	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_EXTI_GPIO_MAPPING(EXTI_config->EXTI_pin.GPIO_port) &0xF) << AFIO_EXTICR_position);

	//============================================================================================
	//3-update Rising or falling register
	EXTI->RTSR &= ~(1<< EXTI_config->EXTI_pin.EXTI_line_number);
	if(EXTI_config->trigger_case == EXTI_Falling){
			EXTI->FTSR |= (1<<EXTI_config->EXTI_pin.EXTI_line_number);
		}
		else if(EXTI_config->trigger_case == EXTI_Rising){
			EXTI->RTSR |= (1<<EXTI_config->EXTI_pin.EXTI_line_number);
		}
		else{
			EXTI->FTSR |= (1<<EXTI_config->EXTI_pin.EXTI_line_number);
			EXTI->RTSR |= (1<<EXTI_config->EXTI_pin.EXTI_line_number);
		}
		//============================================================================================

		//4- update IRQ handling callback
		Gp_IRQ_Callback[EXTI_config->EXTI_pin.EXTI_line_number] = EXTI_config->P_IRQ_Callback;
		//============================================================================================

		//5- enable IRQ in EXTI and NVIC
		if(EXTI_config->IRQ_define == EXTI_IRQ_enable){
			EXTI->IMR |= (1<<EXTI_config->EXTI_pin.EXTI_line_number);
			enable_NVIC(EXTI_config->EXTI_pin.EXTI_line_number);
		}
		else{
			EXTI->IMR &= ~(1<<EXTI_config->EXTI_pin.EXTI_line_number);
			disable_NVIC(EXTI_config->EXTI_pin.EXTI_line_number);
		}

}

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_DeInit
 * @brief 		-Reset EXTI Registers and NVIC IRQ MASk
 * @param      	-none
 * @retval		-none
 * Note			-none
 */

void MCAL_EXTI_GPIO_DeInit()
{
	EXTI->IMR   =  0x00000000;
	EXTI->EMR   =  0x00000000;
	EXTI->RTSR  =  0x00000000;
	EXTI->FTSR  =  0x00000000;
	EXTI->SWIER =  0x00000000;

	EXTI->PR    =  0xFFFFFFFF;	// This bit is set when the selected edge event arrives on the external interrupt line. This bit is
								//  cleared by writing a ‘1’ into the bit.
	//disable the EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_disable();
	NVIC_IRQ7_EXTI1_disable();
	NVIC_IRQ8_EXTI2_disable();
	NVIC_IRQ9_EXTI3_disable();
	NVIC_IRQ10_EXTI4_disable();
	NVIC_IRQ23_EXTI5_to_EXTI9_disable();
	NVIC_IRQ40_EXTI10_to_EXTI15_disable();

}

/**================================================================
 * @Fn                   - MCAL_EXTI_GPIO_INIT
 * @brief                - initialize the GPIO pin  to a specified parameters
 * @param [in]           - config  base on @EXIT_Trigger and  @EXIT_define and @EXIT_IRQ_define
 * @retval               - null
 * Note                  - for stm32f103c6 use only GPIO port A  B C D but package 	LQFP48 has only A  B part of  C D
 *                       - ALSO not no open clock for AFIO and the GPIOX port
 * */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_config)
{
	EXTI_UPDATE(EXTI_config);
}


//================== ISR Functions==========================================


void EXTI0_IRQHandler(void)
{
	EXTI->PR |=(1<<0);
	Gp_IRQ_Callback[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR |=(1<<1);
	Gp_IRQ_Callback[1]();
}

void EXTI2_IRQHandler(void)
{
	EXTI->PR |=(1<<2);
	Gp_IRQ_Callback[2]();
}

void EXTI3_IRQHandler(void)
{
	EXTI->PR |=(1<<3);
	Gp_IRQ_Callback[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |=(1<<4);
	Gp_IRQ_Callback[4]();
}


void EXTI9_5_IRQHandler  (void)
{
	if(EXTI->PR & 1<<5 )   {EXTI->PR |=    (1<<5);     Gp_IRQ_Callback[5](); }
	if(EXTI->PR & 1<<6 )   {EXTI->PR |=    (1<<6);     Gp_IRQ_Callback[6](); }
	if(EXTI->PR & 1<<7)    {EXTI->PR |=    (1<<7);      Gp_IRQ_Callback[7](); }
	if(EXTI->PR & 1<<8 )   {EXTI->PR |=    (1<<8);     Gp_IRQ_Callback[8](); }
	if(EXTI->PR & 1<<9 )   {EXTI->PR |=    (1<<9);     Gp_IRQ_Callback[9](); }
}
void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & 1<<10 )   {EXTI->PR |=    (1<<10);     Gp_IRQ_Callback[10](); }
	if(EXTI->PR & 1<<11 )   {EXTI->PR |=    (1<<11);     Gp_IRQ_Callback[11](); }
	if(EXTI->PR & 1<<12 )   {EXTI->PR |=    (1<<12);     Gp_IRQ_Callback[12](); }
	if(EXTI->PR & 1<<13 )   {EXTI->PR |=    (1<<13);     Gp_IRQ_Callback[13](); }
	if(EXTI->PR & 1<<14 )   {EXTI->PR |=    (1<<14);     Gp_IRQ_Callback[14](); }
	if(EXTI->PR & 1<<15 )   {EXTI->PR |=    (1<<15);     Gp_IRQ_Callback[15](); }
}
//========================================================================================

void enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_enable();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_enable();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_enable();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_enable();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_enable();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_to_EXTI9_enable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:

		NVIC_IRQ40_EXTI10_to_EXTI15_enable();
		break;



	}


}
void disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_disable();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_disable();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_disable();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_disable();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_disable();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_to_EXTI9_disable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:

		NVIC_IRQ40_EXTI10_to_EXTI15_disable();
		break;

	}

}

