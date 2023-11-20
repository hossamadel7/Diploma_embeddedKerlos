/*
 * SPI.c
 *
 * Created: 10/29/2023 7:28:02 PM
 *  Author: KH
 */ 
#include "SPI.h"
#define F_CPU 1000000UL
spi_config* g_SPI_config ;

void MCAL_SPI_Init(spi_config* spi_Config )
{
		g_SPI_config=spi_Config;
		uint8_t	temp_SPCR=0;
		uint8_t	temp_SPSR=0;
		//enable 
		temp_SPCR |= (1<<6);
		//////
		temp_SPCR |= spi_Config->MODE;
		temp_SPCR |=spi_Config->phase;
		temp_SPCR |=spi_Config->polarity;
		temp_SPSR |=spi_Config->Communication_speed;
		temp_SPCR |=spi_Config->baud_rate;
		temp_SPCR |=spi_Config->IRQ_en;
		temp_SPCR |=spi_Config->data_order;
		
		if(spi_Config->IRQ_en== SPI_IRQ_ENABLE_Enable)
		{
			temp_SPCR|=spi_Config->IRQ_en;
			EXTI_GLOBAL_Enable();
		}
		
		SPCR=temp_SPCR;
		SPSR=temp_SPSR;
}

void MCAL_SPI_DeInit( void )
{
	SPCR=0x00;
	SPSR &= ~(1<<0);
}


void MCAL_SPI_Set_Master_Pin( void )
{
	DDRB |= (1<<MOSI) | (1<<SS) | (1<<SCK);
	
	DDRB &= ~(1<<MISO);
}

void MCAL_SPI_Set_Slave_Pin( void )
{
	//Set MISO output
	DDRB |= (1<<MISO);
	//Set MOSI, SCK and SS input
	DDRB &= ~(1<<MOSI) & ~(1<<SCK) & ~(1<<SS);
}

void MCAL_SPI_SendData( uint8_t* PTXBuffer , enum SPI_polling_mechanism polling_EN)
{
	//Start transmission
	SPDR = *PTXBuffer;
	// Wait for transmission complete
	if(polling_EN=Enabled)
	{
		while(!(SPSR & (1<<SPIF)));
	}
	
}
void MCAL_SPI_ReceiveData( uint8_t* PRXBuffer , enum SPI_polling_mechanism polling_EN)
{
	if(polling_EN=Enabled)
	{
		while(!(SPSR & (1<<SPIF)));
	}
	*PRXBuffer=SPDR;
}
void MCAL_SPI_Receive_Send_Data( uint8_t* PRXBuffer , enum SPI_polling_mechanism polling_EN)
{
	if(polling_EN=Enabled)
	{
		while(!(SPSR & (1<<SPIF)));
	}
	SPDR = *PRXBuffer;
	
	if( polling_EN == Enabled)
	{
		while(!(SPSR & (1<<SPIF)));
	}
	*PRXBuffer = SPDR ;
}


/*
 * ===============================================================
 *
 *                      ISR Function Definitions
 *
 * ===============================================================
 */


void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	g_SPI_config->P_IRQ_CALL() ;
}