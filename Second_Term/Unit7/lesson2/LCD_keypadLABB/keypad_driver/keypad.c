/*
 * keypad.c
 *
 * Created: 9/12/2023 3:14:42 AM
 *  Author: KH
 */ 
#include "keypad.h";
int Keypad_r[] = {R0, R1, R2, R3}; //rows of the keypad
int Keypad_c[] = {C0, C1, C2, C3};//columns
	
void KEYPAD_INIT()
{
	Data_dir &= ~((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
	Data_dir |= ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3));
	KEYPAD_PORT = 0xFF;
}
char KEYPAD_getchar(){
	int i,j;
	for (i = 0; i < 4; i++){
		KEYPAD_PORT |= ((1<<Keypad_c[0]) | (1<<Keypad_c[1]) | (1<<Keypad_c[2]) | (1<<Keypad_c[3]));
		KEYPAD_PORT &= ~(1<<Keypad_c[i]);
		for(j = 0; j < 4; j++){
			if (!(keypadPIN & (1 << Keypad_r[j])))
			{
				while(!(keypadPIN & (1 << Keypad_r[j])));
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