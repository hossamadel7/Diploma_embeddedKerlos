/*
 * keypad.c
 *
 * Created: 9/12/2023 3:14:42 AM
 *  Author: KH
 */
#include "keypad.h";
int Keypad_r[] = {R0, R1, R2, R3}; //rows of the keypad
int Keypad_c[] = {C0, C1, C2, C3};//columns

GPIO_PinConfig_t Pincfg;
void KEYPAD_INIT()
{
	//	Data_dir &= ~((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
	Pincfg.GPIO_MODE=GPIO_MODE_INPUT_PU;
	int i;
	for(i=0;i<4;i++)
	{
		Pincfg.GPIO_PinNumber=Keypad_r[i];
		MCAL_GPIO_Init(KEYPAD_PORT, &Pincfg);
	}
	//	Data_dir |= ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3));
	Pincfg.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_Output_Speed=GPIO_SPEED_10M;

	for(i=0;i<4;i++)
	{
		Pincfg.GPIO_PinNumber=Keypad_c[i];
		MCAL_GPIO_Init(KEYPAD_PORT, &Pincfg);
	}
	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}
char KEYPAD_getchar(){
	int i,j;
	for (i = 0; i < 4; i++){
		//		KEYPAD_PORT |= ((1<<Keypad_c[0]) | (1<<Keypad_c[1]) | (1<<Keypad_c[2]) | (1<<Keypad_c[3]));
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_c[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_c[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_c[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_c[3], GPIO_PIN_SET);
		//		KEYPAD_PORT &= ~(1<<Keypad_c[i]);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_c[i], GPIO_PIN_RESET);
		for(j = 0; j < 4; j++){
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Keypad_r[j])==0)
			{
				//(keypadPIN & (1 << Keypad_r[j]))
				while( MCAL_GPIO_ReadPin(KEYPAD_PORT, Keypad_r[j])==0 );
				switch(i){
				case (0):
											if (j == 0) return '7';
											else if (j == 1) return '4';
											else if (j == 2) return '1';
											else if (j == 3) return '?';
				break;
				case (1):
											if (j == 0) return '8';
											else if (j == 1) return '5';
											else if (j == 2) return '2';
											else if (j == 3) return '0';
				break;
				case (2):
											if (j == 0) return '9';
											else if (j == 1) return '6';
											else if (j == 2) return '3';
											else if (j == 3) return '=';
				break;
				case (3):
											if (j == 0) return '/';
											else if (j == 1) return '*';
											else if (j == 2) return '-';
											else if (j == 3) return '+';
				break;
				}
			}
		}
	}
	return 'A';
}
