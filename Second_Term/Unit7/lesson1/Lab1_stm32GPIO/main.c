#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//clock
#define RCC_BASE     0x40021000
#define RCC_APB2ENR  *(volatile uint32_t *) (RCC_BASE + 0x18)

//GPIO
#define GPIOA_BASE   0x40010800
#define GPIOA_CRL   *(volatile uint32_t *) (GPIOA_BASE + 0x00)
#define GPIOA_CRH   *(volatile uint32_t *) (GPIOA_BASE + 0x04)
#define GPIOA_ODR   *(volatile uint32_t *) (GPIOA_BASE + 0x0C)
#define GPIOA_IDR   *(volatile uint32_t *) (GPIOA_BASE + 0x08)


#define GPIOB_BASE   0x40010C00
#define GPIOB_CRL  *(volatile uint32_t *) (GPIOB_BASE + 0x00)
#define GPIOB_CRH   *(volatile uint32_t *) (GPIOB_BASE + 0x04)
#define GPIOB_ODR   *(volatile uint32_t *) (GPIOB_BASE + 0x0C)
#define GPIOB_IDR   *(volatile uint32_t *) (GPIOB_BASE + 0x08)


void clock_init(){
	//enable clock for GPIOA
	RCC_APB2ENR |= (1<<2);

	//enable clock for GPIOB
	RCC_APB2ENR |= (1<<3);

}

void GPIO_init(){
	GPIOA_CRH=0;
	GPIOA_CRL=0;
	GPIOA_ODR=0;

	//input bins will be open-drain
	//PA1 input HighZ
		GPIOA_CRL &= ~(0b11 <<4);
		GPIOA_CRL |= (0b01<<6);

	//PB1 output push-pull
		GPIOB_CRL =0x0;

		GPIOB_CRL |=(0b01<<4);
		GPIOB_CRL &= ~(0b11<<6);

  //PA13 input HighZ
		GPIOA_CRH &= ~(0b11 <<20);
		GPIOA_CRH |= (0b01 <<22);
	//PB13 output
		GPIOB_CRH |=(0b01 <<20);
		GPIOB_CRH &= ~(0b11 <<22);
}


void mywait(int x)
{
	int i;
	for(i=0;i<x;i++);
}

int main(void)
{
	clock_init();
	GPIO_init();

	while(1)
	{
		if( ((GPIOA_IDR & (1<<1)) >>1) ==0 ) //press
		{
				GPIOB_ODR ^=1<<1 ;
				while(((GPIOA_IDR & (1<<1)) >>1) ==0);

		}
		if( ((GPIOA_IDR & (1<<13)) >>13) ==1 ) //press
		{
				GPIOB_ODR ^=1<<13 ;
		}
		mywait(1000);
	}
	return 0;
}



