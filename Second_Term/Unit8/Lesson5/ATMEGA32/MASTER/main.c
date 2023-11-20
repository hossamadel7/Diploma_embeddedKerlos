/*
 * Unit7_lesson2Lab1.c
 *
 * Created: 9/11/2023 7:19:29 PM
 * Author : KH
 */ 

#include "lcd_driver/lcd.h"
#include "keypad_driver/keypad.h"
#include "SPI_driver/SPI.h"
#define F_CPU 1000000UL





int main(void)
{
	spi_config spiCFG;
    spiCFG.baud_rate=SPI_BaudRate_Prescalers_4;
    spiCFG.MODE=SPI_MODE_Master;
    spiCFG.data_order=SPI_Data_Order_MSB_Transmitted_First;
    spiCFG.Communication_speed=SPI_SPEED_normal;
    spiCFG.IRQ_en=SPI_IRQ_ENABLE_Disable;
    spiCFG.phase=SPI_Phase_Sample;
    spiCFG.polarity=SPI_Polarity_LOW_IDLE;
	
	uint8_t data='A',rece_data;
	
	LCD_INIT();
	MCAL_SPI_Init(&spiCFG);
	MCAL_SPI_Set_Master_Pin();
    _delay_ms(50);
	
	LCD_WRITE_STRING("MASTER ");
	
    while(1){
		MCAL_SPI_SendData(&data,Enabled);
		MCAL_SPI_ReceiveData(&rece_data,Enabled);
		
		data++;
	    if(data== 'Z'+1)
		{
			data='A';
		}
		LCD_GOTO_XY(1,0);
		LCD_WRITE_CHAR(rece_data);
	
	}
}
