/*
 * stm32_f103c6_GPIO.c
 *
 *  Created on: Sep 13, 2023
 *      Author: KH
 */


#include "stm32_f103c6_USART.h"

USART_config* Global_USART_Config[3] = {NULL,NULL,NULL};
/**================================================================
 * @Fn                   -MCAL_USART_Init
 * @brief                -initialize the USARTX pin  to a specified parameters
 * @param [in]           -USARTX where x can be (USARTX1 USARTX2 USART3)
 * @retval               - null
 * Note                  -null
 */
void MCAL_USART_Init(USART_TypeDef* USARTx, USART_config* USART_cfg){

	uint32_t pclk, BRR;

	if(USARTx==USART1)
	{
		Global_USART_Config[0]=USART_cfg;
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2){
		Global_USART_Config[1] = USART_cfg;
		RCC_USART2_CLK_EN();
	}
	else{
		Global_USART_Config[2] = USART_cfg;
		RCC_USART3_CLK_EN();
	}
	//enable USART module
	USARTx->CR1 |= 1<<13;

	//-----------all of the following configs corresponding bits in the registers are already done in the reference macros---------

	//enable TX/RX according to config
	USARTx->CR1 |= USART_cfg->USART_MODE;

	//payload length
	USARTx->CR1 |= USART_cfg->Payload_length;

	//parity bits
	USARTx->CR1 |= USART_cfg->Parity;

	//stop bits
	USARTx->CR2 |= USART_cfg->Stop_bits;

	//control flow
	USARTx->CR3 |= USART_cfg->HW_Flow_Control;

	//-----------------------------------------------------------------------------------------------------------


	//------------------------------------Baud rate configuration------------------------------------------------
	//PCLK1 for USART2,3
	//PCLK2 for USART1

	if(USARTx == USART1){
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}
	//details in @ref Baud rate calculation
	BRR = USART_BRR_Register(pclk,USART_cfg->Baud_rate);
	USARTx->BRR = BRR;
	//-------------------------------------------------------------------------------------------------------------		\
	//Enable/Disable interrupt

	if(USART_cfg->IRQ_Enable != USART_IRQ_ENABLE_NONE){
		USARTx->CR1 |= (USART_cfg->IRQ_Enable);

		//enable NVIC for USARTx
		if(USARTx == USART1){
			NVIC_IRQ37_USART1_enable();
		}
		else if(USARTx == USART2){
			NVIC_IRQ38_USART2_enable();
		}
		else{
			NVIC_IRQ39_USART3_enable();
		}
	}
}

/**================================================================
 * @Fn                   -MCAL_USART_DEInit
 * @brief                -deinitialize the USARTX pin  to a specified parameters
 * @param [in]           -USARTX where x can be (USARTX1 USARTX2 USART3)
 * Note                  -null
 */
void MCAL_USART_DeInit(USART_TypeDef* USARTx){

	//disable interrupt and clock
	if(USARTx == USART1){
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_disable();
	}
	else if(USARTx == USART2){
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_disable();
	}
	else{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_disable();
	}

}

void MCAL_USART_Send_Data(USART_TypeDef* USARTx, uint16_t* Data, enum Polling_Mechanism PollingEN ){

	USART_config* USART_CFG = NULL;
	if(USARTx == USART1){
		USART_CFG = Global_USART_Config[0];
	}
	else if(USARTx == USART2){
		USART_CFG = Global_USART_Config[1];
	}
	else{
		USART_CFG = Global_USART_Config[2];
	}
	//check if TXE is set in SR
	if(PollingEN == enable){
		while(!(USARTx->SR & 1<<7));
	}

	//check payload length
	if(USART_CFG->Payload_length == USART_Payload_Length_8){
		USARTx->DR = (*Data & (uint8_t)0xFF);
	}
	else{
		USARTx->DR = (*Data & (uint16_t)0x1FF);
	}
}

void MCAL_USART_Receive_Data(USART_TypeDef* USARTx, uint16_t* Data, enum Polling_Mechanism PollingEN ){

	//When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//because it is replaced by the parity.
	//When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.


	USART_config* USART_CFG = NULL;
	if(USARTx == USART1){
		USART_CFG = Global_USART_Config[0];
	}
	else if(USARTx == USART2){
		USART_CFG = Global_USART_Config[1];
	}
	else{
		USART_CFG = Global_USART_Config[2];
	}
	//check if RXNE is set in SR
	if(PollingEN == enable){
		while(!(USARTx->SR & 1<<5));
	}

	//check payload length
	if(USART_CFG->Payload_length == USART_Payload_Length_8){

		//if no parity
		if(USART_CFG->Parity == USART_Parity_NONE){
			*Data = USARTx->DR;
		}
		else{
			*Data = (USARTx->DR & (uint8_t)0x7F);
		}
	}
	else{

		//if no parity
		if(USART_CFG->Parity == USART_Parity_NONE){
			*Data = USARTx->DR;
		}
		else{
			*Data = (USARTx->DR & (uint8_t)0xFF);
		}
	}
}

void MCAL_USART_Wait_TC(USART_TypeDef* USARTx){

	//wait till TC flag is set in SR
	while(!(USARTx->SR & 1<<6));
}

void MCAL_USART_GPIO_Set_Pins(USART_TypeDef* USARTx){

	USART_config* USART_CFG = NULL;
	if(USARTx == USART1){
		USART_CFG = Global_USART_Config[0];
	}
	else if(USARTx == USART2){
		USART_CFG = Global_USART_Config[1];
	}
	else{
		USART_CFG = Global_USART_Config[2];
	}


	GPIO_PinConfig_t USART_pincfg;

	if(USARTx == USART1){
		//PA9->TX, PA10-> RX, PA11-> CTS, PA12-> RTS

		//PA9 TX
		USART_pincfg.GPIO_PinNumber =GPIO_PIN9;
		USART_pincfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
		USART_pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		//PA10 RX
		USART_pincfg.GPIO_PinNumber =GPIO_PIN10;
		USART_pincfg.GPIO_MODE= GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		//PA11 CTS
		if(USART_CFG->HW_Flow_Control == USART_Flow_Control_CTS_ENABLE ||
				USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_CTS_ENABLE){

			USART_pincfg.GPIO_PinNumber =GPIO_PIN11;
			USART_pincfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		}

		//PA12 RTS
		if(USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_ENABLE ||
				USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_CTS_ENABLE){

			USART_pincfg.GPIO_PinNumber =GPIO_PIN12;
			USART_pincfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			USART_pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		}

	}
	else if(USARTx == USART2){

		//PA2->TX, PA3-> RX, PA0-> CTS, PA1-> RTS

		//PA2 TX
		USART_pincfg.GPIO_PinNumber =GPIO_PIN2;
		USART_pincfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
		USART_pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		//PA3 RX
		USART_pincfg.GPIO_PinNumber =GPIO_PIN3;
		USART_pincfg.GPIO_MODE= GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		//PA0 CTS
		if(USART_CFG->HW_Flow_Control == USART_Flow_Control_CTS_ENABLE ||
				USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_CTS_ENABLE){

			USART_pincfg.GPIO_PinNumber =GPIO_PIN0;
			USART_pincfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		}

		//PA1 RTS
		if(USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_ENABLE ||
				USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_CTS_ENABLE){

			USART_pincfg.GPIO_PinNumber =GPIO_PIN1;
			USART_pincfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			USART_pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &USART_pincfg);

		}
	}
	else{

		//PB10->TX, PB11-> RX, PB13-> CTS, PB14-> RTS

		//PB10 TX
		USART_pincfg.GPIO_PinNumber =GPIO_PIN10;
		USART_pincfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
		USART_pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB , &USART_pincfg);

		//PB11 RX
		USART_pincfg.GPIO_PinNumber =GPIO_PIN11;
		USART_pincfg.GPIO_MODE= GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB , &USART_pincfg);

		//PB13 CTS
		if(USART_CFG->HW_Flow_Control == USART_Flow_Control_CTS_ENABLE ||
				USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_CTS_ENABLE){

			USART_pincfg.GPIO_PinNumber =GPIO_PIN13;
			USART_pincfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOB , &USART_pincfg);

		}

		//PB14 RTS
		if(USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_ENABLE ||
				USART_CFG->HW_Flow_Control == USART_Flow_Control_RTS_CTS_ENABLE){

			USART_pincfg.GPIO_PinNumber =GPIO_PIN14;
			USART_pincfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			USART_pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB , &USART_pincfg);

		}

	}
}

//ISR
void USART1_IRQHandler()
{
	Global_USART_Config[0]->P_IRQ_Callback;

}

void USART2_IRQHandler()
{
	Global_USART_Config[1]->P_IRQ_Callback;

}

void USART3_IRQHandler()
{
	Global_USART_Config[2]->P_IRQ_Callback;

}
