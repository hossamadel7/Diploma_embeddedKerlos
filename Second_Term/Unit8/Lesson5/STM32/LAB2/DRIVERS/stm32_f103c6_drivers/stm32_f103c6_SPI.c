/*
 * stm32_f103c6_SPI.c
 *
 *  Created on: Oct 20, 2023
 *      Author: KH
 */
#include "stm32_f103c6_SPI.h"

/*
 * =====================================================================================
 * 							Generic Variables
 * =====================================================================================
 */

SPI_config* Global_SPI_Config[2] = {NULL,NULL};


/*
 * =====================================================================================
 * 							Generic Macros
 * =====================================================================================
 */

#define SPI1_INDEX    0
#define SPI2_INDEX    1

#define SPI_SR_TXE				((uint8_t)(0x02)) // Transmit Buffer is empty
#define SPI_SR_RXNE				((uint8_t)(0x01)) // Receive Buffer is not empty


/**================================================================
 * @Fn			 -MCAL_SPI_Init
 * @brief 		 -Initialize SPI according to the specified parameters in SPI_Config
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]   -PinConfig : pointer to SPI_Config Structure that Contains
 * 						      the configuration information for All SPI.
 * @retval		 -none
 * Note			 -Support for SPI Full Duplex Master/Slave & NSS HW/SW
 * 				 -In Case of Master you have to Configure pin and drive it.
 */
void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_config* SPI_cfg)
{
	//Safety for registers to put the result in the original register at the end
	uint16_t temp_reg_CR1 = 0 ;
	uint16_t temp_reg_CR2 = 0 ;
	if(SPIx==SPI1)
	{
		RCC_SPI1_CLK_EN();
		Global_SPI_Config[SPI1_INDEX]=SPI_cfg;

	}
	if(SPIx==SPI2)
	{
		RCC_SPI2_CLK_EN();
		Global_SPI_Config[SPI2_INDEX]=SPI_cfg;
	}

	//enable SPI
	temp_reg_CR1 = (1<<6);

	//-----------all of the following configs corresponding bits in the registers are already done in the reference macros---------
	temp_reg_CR1 |= SPI_cfg->Device_Mode;

	temp_reg_CR1 |= SPI_cfg->Comm_Mode;

	temp_reg_CR1 |= SPI_cfg->Frame_Format;

	temp_reg_CR1 |= SPI_cfg->Data_size;

	temp_reg_CR1 |= SPI_cfg->Clock_Polarity;

	temp_reg_CR1 |= SPI_cfg->Clock_Phase;

	temp_reg_CR1 |= SPI_cfg->SPI_Clock_Freq;

	//config NSS
	if(SPI_cfg->NSS==SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE)
	{
		temp_reg_CR2|= SPI_cfg->NSS;
	}
	else if(SPI_cfg->NSS==SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE)
	{
		temp_reg_CR2 &=  SPI_cfg->NSS;
	}
	else
	{
		temp_reg_CR1|= SPI_cfg->NSS;
	}
	//=======================================================
	//IRQ

	if(SPI_cfg->IRQ_Enable != SPI_IRQ_ENABLE_NONE){
		temp_reg_CR2 |= SPI_cfg->IRQ_Enable;
		if(SPIx == SPI1){
			NVIC_IRQ35_SPI1_enable();
		}
		else{
			NVIC_IRQ36_SPI2_enable();
		}
	}

	SPIx->CR1 = temp_reg_CR1;
	SPIx->CR2 = temp_reg_CR2;

}

/**================================================================
 * @Fn			 -MCAL_SPI_DeInit
 * @brief 		 -Reset SPI Registers and NVIC corresponding to IRQ Mask
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @retval		 -none
 * Note			 -none
 */
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx){

	if(SPIx == SPI1){

		RCC_SPI1_CLK_RESET();
		NVIC_IRQ35_SPI1_disable();
	}
	else{
		RCC_SPI2_CLK_RESET();
		NVIC_IRQ36_SPI2_disable();
	}

}

void MCAL_SPI_Send_Data(SPI_TypeDef* SPIx, uint16_t* Data, enum Polling_Mechanismm PollingEN )
{
	if(PollingEN==pollingenable)
	{while(!(SPIx->SR & SPI_SR_TXE));}

	SPIx->DR=*Data;

}

void MCAL_SPI_Receive_Data(SPI_TypeDef* SPIx, uint16_t* Data, enum Polling_Mechanismm PollingEN ){

	if(PollingEN == pollingenable){
		while(!((SPIx->SR) & SPI_SR_RXNE));
	}

	*Data = SPIx->DR;
}

void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx, uint16_t* Data, enum Polling_Mechanismm PollingEN ){

	if(PollingEN == pollingenable){
		while(!((SPIx->SR) & SPI_SR_TXE));
	}

	SPIx->DR = *Data;

	if(PollingEN == pollingenable){
		while(!((SPIx->SR) & SPI_SR_RXNE));
	}

	*Data = SPIx->DR;
}



void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx){

	GPIO_PinConfig_t pin_cfg;

	if(SPIx==SPI1)
	{
		//   PA4:NSS
		//   PA5:SCK
		//   PA6:MISO
		//	 PA7:MOSI
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode==SPI_DEVICE_MODE_MASTER)
		{
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE:
				pin_cfg.GPIO_PinNumber =GPIO_PIN4;
				pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
				MCAL_GPIO_Init(GPIOA , &pin_cfg);

				break;


			case SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE:
				pin_cfg.GPIO_PinNumber =GPIO_PIN4;
				pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
				pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA , &pin_cfg);
				break;
			}

			//PA5: SCLK
			pin_cfg.GPIO_PinNumber =GPIO_PIN5;
			pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);


			//PA6: MISO
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN6;
			pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);


			//PA7: MOSI
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN7;
			pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
		}

		//Slave
		else{

			if(Global_SPI_Config[SPI1_INDEX]->NSS== SPI_NSS_HARDWARE_SLAVE){
				//PA4: NSS
				pin_cfg.GPIO_PinNumber =GPIO_PIN4;
				pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
				MCAL_GPIO_Init(GPIOA , &pin_cfg);
			}


			//PA5: SCLK
			pin_cfg.GPIO_PinNumber =GPIO_PIN5;
			pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);

			//PA6: MISO
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN6;
			pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);

			//PA7: MOSI
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN7;
			pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOA , &pin_cfg);
		}

	}
	else
	{
		SPI_config *spi_cfg = Global_SPI_Config[SPI2_INDEX];

		//Master
		if(spi_cfg->Device_Mode == SPI_DEVICE_MODE_MASTER){

			//PB12: NSS
			switch(spi_cfg->NSS){

			case SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE:
				pin_cfg.GPIO_PinNumber =GPIO_PIN12;
				pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
				MCAL_GPIO_Init(GPIOB , &pin_cfg);
				break;


			case SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE:
				pin_cfg.GPIO_PinNumber =GPIO_PIN12;
				pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
				pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB , &pin_cfg);
				break;
			}

			//PA5: SCLK
			pin_cfg.GPIO_PinNumber =GPIO_PIN13;
			pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);


			//PA6: MISO
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN14;
			pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);


			//PA7: MOSI
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN15;
			pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);
		}

		//Slave
		else{

			if(spi_cfg->NSS == SPI_NSS_HARDWARE_SLAVE){
				//PA4: NSS
				pin_cfg.GPIO_PinNumber =GPIO_PIN12;
				pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
				MCAL_GPIO_Init(GPIOB , &pin_cfg);
			}


			//PA5: SCLK
			pin_cfg.GPIO_PinNumber =GPIO_PIN13;
			pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);

			//PA6: MISO
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN14;
			pin_cfg.GPIO_MODE= GPIO_MODE_OUTPUT_AF_PP;
			pin_cfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);

			//PA7: MOSI
			//full duplex
			pin_cfg.GPIO_PinNumber =GPIO_PIN15;
			pin_cfg.GPIO_MODE= GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_Init(GPIOB , &pin_cfg);
		}
	}

}

/*
 * =====================================================================================
 * 							ISR Functions
 * =====================================================================================
 */

void SPI1_IRQHandler(void)
{
	struct SPI_IRQ_SRC irq_src ;

	irq_src.TXE  = ( ( SPI1->SR  & (1<<1)) >>1  ) ;
	irq_src.RXNE = ( ( SPI1->SR  & (1<<0)) >> 0 ) ;
	irq_src.ERRI = ( ( SPI1->SR  & (1<<4)) >> 4 ) ;

	Global_SPI_Config[SPI1_INDEX]->P_IRQ_Callback(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct SPI_IRQ_SRC irq_src ;

	irq_src.TXE  = ( ( SPI2->SR  & (1<<1)) >> 1 ) ;
	irq_src.RXNE = ( ( SPI2->SR  & (1<<0)) >> 0 ) ;
	irq_src.ERRI = ( ( SPI2->SR  & (1<<4)) >> 4 ) ;

	Global_SPI_Config[SPI2_INDEX]->P_IRQ_Callback(irq_src);
}

