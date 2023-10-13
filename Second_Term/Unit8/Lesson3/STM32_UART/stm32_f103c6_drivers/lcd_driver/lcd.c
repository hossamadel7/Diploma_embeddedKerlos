#include "lcd.h"
uint16_t GPIO_PINS[16]={GPIO_PIN0,GPIO_PIN1,GPIO_PIN2,GPIO_PIN3,GPIO_PIN4,GPIO_PIN5,GPIO_PIN6,GPIO_PIN7,GPIO_PIN8,GPIO_PIN9,GPIO_PIN10,GPIO_PIN11,GPIO_PIN12,GPIO_PIN13,GPIO_PIN14,GPIO_PIN15};

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_lcd_kick(){
	//LCD_CTRL |= (1 << EN_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
	my_wait_ms(50);
	//LCD_CTRL &= ~(1 << EN_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

GPIO_PinConfig_t Pincfg;
int i=0;

void LCD_INIT(){
	my_wait_ms(20);
	Pincfg.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;

	Pincfg.GPIO_PinNumber=EN_SWITCH;
	MCAL_GPIO_Init(GPIOA, &Pincfg);

	Pincfg.GPIO_PinNumber=RS_SWITCH;
	MCAL_GPIO_Init(GPIOA, &Pincfg);

	Pincfg.GPIO_PinNumber=RW_SWITCH;
	MCAL_GPIO_Init(GPIOA, &Pincfg);


	//	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	//	LCD_CTRL &= ~ (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	//DataDir_LCD_PORT = 0xFF;

#ifdef EIGHT_BIT_MODE
	Pincfg.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	for(int i = 0; i<8; i++){
			Pincfg.GPIO_PinNumber = GPIO_PINS[i];
			MCAL_GPIO_Init(LCD_PORT, &Pincfg);
	}

	my_wait_ms(15);
	LCD_clear_screen();
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
#endif
#ifdef FOUR_BIT_MODE
	//LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
	//LCD_WRITE_COMMAND(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	//LCD_WRITE_COMMAND(0x0c);              /* Display on cursor off*/
	//LCD_WRITE_COMMAND(0x06);              /* Increment cursor (shift cursor to right)*/
	//LCD_WRITE_COMMAND(0x01);
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_check_lcd_isbusy(){

	//DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);
	Pincfg.GPIO_MODE=GPIO_MODE_INPUT_FLOAT;
	for(int i = 0; i<8; i++){
			Pincfg.GPIO_PinNumber = GPIO_PINS[i];
			MCAL_GPIO_Init(LCD_PORT, &Pincfg);
	}

	//LCD_CTRL |= (1 << RW_SWITCH);
	//LCD_CTRL &= ~(1 << RS_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	LCD_lcd_kick();


	//DataDir_LCD_PORT |= (0xFF<<DATA_shift);
	Pincfg.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	for(int i = 0; i<8; i++){
			Pincfg.GPIO_PinNumber = GPIO_PINS[i];
			MCAL_GPIO_Init(LCD_PORT, &Pincfg);
	}

	//LCD_CTRL &= ~(1 << RW_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);


}


void LCD_WRITE_COMMAND(unsigned char command){
#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	//LCD_PORT = command;
	MCAL_GPIO_WritePort(LCD_PORT, command);

	//LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	my_wait_ms(20);
	LCD_lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_lcd_kick ();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_lcd_kick();
#endif
}

void LCD_WRITE_CHAR(unsigned char character){
#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	//LCD_PORT = character;
	MCAL_GPIO_WritePort(LCD_PORT, character);

	//LCD_CTRL &= ~(1 << RW_SWITCH);
	//LCD_CTRL |= (1 << RS_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	my_wait_ms(1);
	LCD_lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
	//LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
	LCD_lcd_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
	LCD_lcd_kick ();
#endif
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}

void my_wait_ms (int x)
{
	uint32_t i , j ;
	for (i= 0 ; i<x ; i++)
		for (j= 0 ; j<255 ; j++);
}
