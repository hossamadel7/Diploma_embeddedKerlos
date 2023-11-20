/*
 * SPI.h
 *
 * Created: 10/29/2023 7:28:43 PM
 *  Author: KH
 */ 


#ifndef SPI_H_
#define SPI_H_


#include<avr/io.h>
#include<util/delay.h>
#define F_CPU 1000000UL

typedef struct
{
	uint8_t MODE;			//specified the SPI (Master / slave) to be configured .
							//this parameter must be set based on  @ ref  SPI_MODE_Define
	uint8_t Communication_speed;	//specified the SPI SPEED to be double or not configured .
							//this parameter must be set based on  @ ref  SPI_SPEED_Define
	uint8_t baud_rate;		//specified the baudrate prescalers .
							//this parameter must be set based on  @ ref  SPI_BaudRate_Prescalers_Define
	uint8_t polarity;		//specified the Polarity  .
							//this parameter must be set based on  @ ref  SPI_Polarity_Define
	uint8_t phase;			//specified the Phase.
							//this parameter must be set based on  @ ref  SPI_Phase_Define
	uint8_t data_order;		//specified the Programmable data order with MSB-first or LSB-first shifting .
							//this parameter must be set based on  @ ref  SPI_Data_Order_Define
	uint8_t IRQ_en;			//specified the interrupt (disable or enable )  .
							//this parameter must be set based on  @ ref  SPI_IRQ_ENABLE_Define
	
	void (*P_IRQ_CALL)()
	
}spi_config;

enum SPI_polling_mechanism
{
	Enabled ,
	Disabled
};

/* ================================================================ */
/* =============== Macros Configuration References ================ */
/* ================================================================ */

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

// @ ref  SPI_MODE_Define
#define  SPI_MODE_Master	(uint8_t) (1<<4)
#define  SPI_MODE_Slave		(uint8_t) (0)

//@ ref  SPI_BaudRate_Prescalers_Define
/*
Bits 5:3 BR[2:0]: Baud rate control
00: fPCLK/4
01: fPCLK/16
10: fPCLK/64
11: fPCLK/128
 */
#define SPI_BaudRate_Prescalers_4							(uint8_t)(0)
#define SPI_BaudRate_Prescalers_16							(uint8_t)(1<<0)
#define SPI_BaudRate_Prescalers_64							(uint8_t)(2<<0)
#define SPI_BaudRate_Prescalers_128							(uint8_t)(3<<0)

//@ ref  SPI_Speed_Communication_Define
#define  SPI_SPEED_normal	(uint8_t) (0)
#define  SPI_SPEED_double	(uint8_t) (1<<0)

#define  SPI_Polarity_LOW_IDLE	(uint8_t) (0)	
#define  SPI_Polarity_HIGH_IDLE	(uint8_t) (1<<3)

#define  SPI_Phase_Sample	(uint8_t) (0)
#define  SPI_Phase_Setup	(uint8_t) (1<<2)

#define SPI_Data_Order_MSB_Transmitted_First				(uint8_t)(0)
#define SPI_Data_Order_LSB_Transmitted_First				(uint8_t)(1<<5)

//@ ref  SPI_IRQ_ENABLE_Define
#define SPI_IRQ_ENABLE_Enable								(uint8_t)(1<<7)
#define SPI_IRQ_ENABLE_Disable								(uint8_t)(0)

#define SPI_Enable()										(uint8_t)(1<<6)
#define SPI_Disable()										(uint8_t)(0)
/////////////////////
#define EXTI_GLOBAL_Enable()							(SREG |=1<<7)

//////
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_SPI_Init(spi_config* spi_Config );
void MCAL_SPI_DeInit( void );
void MCAL_SPI_Set_Master_Pin( void );
void MCAL_SPI_ReceiveData( uint8_t* PRXBuffer , enum SPI_polling_mechanism polling_EN);
void MCAL_SPI_SendData( uint8_t* PTXBuffer , enum SPI_polling_mechanism polling_EN);
void MCAL_SPI_Receive_Send_Data( uint8_t* PRXBuffer , enum SPI_polling_mechanism polling_EN);
void MCAL_SPI_Set_Slave_Pin( void );
//===============================================================================

#endif /* SPI_H_ */