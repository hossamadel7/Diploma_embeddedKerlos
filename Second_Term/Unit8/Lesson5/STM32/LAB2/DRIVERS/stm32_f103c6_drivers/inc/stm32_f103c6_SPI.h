/*
 * stm32_f103c6_SPI.h
 *
 *  Created on: Oct 20, 2023
 *      Author: KH
 */

#ifndef INC_STM32_F103C6_SPI_H_
#define INC_STM32_F103C6_SPI_H_

#include "stm32f103x6.h"
#include "stm32_f103c6_GPIO.h"

//to pass to the IRQ_CALLBACK function to know the source of the interrupt
struct SPI_IRQ_SRC{
	uint8_t TXE:1;  //TX buffer empty interrupt
	uint8_t RXNE:1;  //RX buffer not empty interrupt
	uint8_t ERRI:1;  //Error interrupt
	uint8_t Reserved:5;
};


typedef struct{

	uint16_t    Device_Mode;      //specify SPI operating mode  @ref SPI_DEVICE_MODE

	uint16_t    Comm_Mode;        //specify the SPI bidirectional mode state   @ref SPI_COMMUNICATION_MODE

	uint16_t    Frame_Format;     //specify LSB or MSB first   @ref SPI_FRAME_FORMAT

	uint16_t    Data_size;        //@ref SPI_DATA_SIZE

	uint16_t    Clock_Polarity;   //@ref SPI_CLOCK_POLARITY

	uint16_t    Clock_Phase;      //@ref SPI_CLOCK_PHASE

	uint16_t    NSS;             //specify whether the NSS signal is managed by hardware (NSS pin)
	                            //or by software   @ref  SPI_NSS

	uint16_t    SPI_Clock_Freq;  //specify the baud rate prescaler value which will be used to
								//to configure the transmit and receive clock
								//@ref SPI_CLOCK_FREQUENCY

	uint16_t    IRQ_Enable;		// @ref SPI_IRQ_enable

	void(*P_IRQ_Callback)(struct SPI_IRQ_SRC irq_src);    //set the function which will be called when the IRQ happen

}SPI_config;



//=================================================================================
//Macros Configuration References
//=================================================================================


//@ref SPI_DEVICE_MODE
#define SPI_DEVICE_MODE_SLAVE              (uint32_t)(0)
#define SPI_DEVICE_MODE_MASTER             (uint32_t)(1<<2)


//@ref SPI_COMMUNICATION_MODE
#define SPI_COMM_MODE_2LINES_TX_RX         (uint32_t)(0)
#define SPI_COMM_MODE_2LINES_RX            (uint32_t)(1<<10)
#define SPI_COMM_MODE_1LINE_Receive        (uint32_t)(1<<15)
#define SPI_COMM_MODE_1LINE_Transmit       ((uint32_t)(1<<15 | 1<<14))


//@ref SPI_FRAME_FORMAT
#define SPI_FRAME_LSB_FIRST                (uint32_t)(1<<7)
#define SPI_FRAME_MSB_FIRST                (uint32_t)(0)


//@ref SPI_DATA_SIZE
#define SPI_DATA_SIZE_8_BIT                (uint32_t)(0)
#define SPI_DATA_SIZE_16_BIT               (uint32_t)(1<<11)


//@ref SPI_CLOCK_POLARITY
#define SPI_CLOCK_POLARITY_LOW_WHEN_IDLE   (uint32_t)(0)
#define SPI_CLOCK_POLARITY_HIGH_WHEN_IDLE  (uint32_t)(1<<1)


//@ref SPI_CLOCK_PHASE
#define SPI_CLOCK_PHASE_FIRST_EDGE         (uint32_t)(0)
#define SPI_CLOCK_PHASE_SECOND_EDGE        (uint32_t)(1<<0)


//@ref SPI_NSS

//Hardware
#define SPI_NSS_HARDWARE_SLAVE                        (uint32_t)(0) //SSM bit in SPI_CR1 register
#define SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_DISABLE     ~(uint32_t)(1<<2) //SSOE bit in SPI_CR2 register
#define SPI_NSS_HARDWARE_MASTER_SS_OUTPUT_ENABLE      (uint32_t)(1<<2) ///SSOE bit in SPI_CR2 register

//Software
//we control the value of the NSS pin through a bit(SSI) in a register(SPI_CR1)

#define SPI_NSS_SOFTWARE_INTERNAL_SS_RESET            (uint32_t)(1<<9) //SSM bit in SPI_CR1 register (SSI bit is 0)
#define SPI_NSS_SOFTWARE_INTERNAL_SS_SET              (uint32_t)(1<<9 | 1<<8) //(SSM bit | SSI bit) in SPI_CR1 register


//@ref SPI_CLOCK_FREQUENCY
#define SPI_BAUD_RATE_PRESCALER_2          (uint32_t)(0)
#define SPI_BAUD_RATE_PRESCALER_4          (uint32_t)(0b001 << 3)
#define SPI_BAUD_RATE_PRESCALER_8          (uint32_t)(0b010 << 3)
#define SPI_BAUD_RATE_PRESCALER_16         (uint32_t)(0b011 << 3)
#define SPI_BAUD_RATE_PRESCALER_32         (uint32_t)(0b100 << 3)
#define SPI_BAUD_RATE_PRESCALER_64         (uint32_t)(0b101 << 3)
#define SPI_BAUD_RATE_PRESCALER_128        (uint32_t)(0b110 << 3)
#define SPI_BAUD_RATE_PRESCALER_256        (uint32_t)(0b111 << 3)


// @ref SPI_IRQ_enable
#define SPI_IRQ_ENABLE_NONE                (uint32_t)(0)
#define SPI_IRQ_ENABLE_TXEIE               (uint32_t)(1<<7)
#define SPI_IRQ_ENABLE_RXNIE               (uint32_t)(1<<6)
#define SPI_IRQ_ENABLE_ERRIE               (uint32_t)(1<<5)

enum Polling_Mechanismm{
	pollingenable,
	pollingdisable
};



//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-
// APIS Supported by "MCAL SPI DRIVER"
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-

void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_config* SPI_cfg);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx);

void MCAL_SPI_Send_Data(SPI_TypeDef* SPIx, uint16_t* Data, enum Polling_Mechanismm PollingEN );
void MCAL_SPI_Receive_Data(SPI_TypeDef* SPIx, uint16_t* Data, enum Polling_Mechanismm PollingEN );

void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx, uint16_t* Data, enum Polling_Mechanismm PollingEN );


#endif /* INC_STM32_F103C6_SPI_H_ */
