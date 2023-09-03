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
#define GPIOA_CRL    *(volatile uint32_t *) (GPIOA_BASE + 0x00)
#define GPIOA_CRH    *(volatile uint32_t *) (GPIOA_BASE + 0x04)
#define GPIOA_ODR    *(volatile uint32_t *) (GPIOA_BASE + 0x0c)


//EXTI
#define EXTI_BASE 	0x40010400
#define EXTI_IMR	*(volatile uint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR	*(volatile uint32_t *)(EXTI_BASE + 0x08)
#define EXTI_PR		*(volatile uint32_t *)(EXTI_BASE + 0x14)


//AFIO

#define AFIO_BASE 	0x40010000
//bits[3:0] in this register selects which port to map to EXTI line 0
#define AFIO_EXTICR1 *(volatile uint32_t *)(AFIO_BASE + 0x08)

//NVIC
#define NVIC_EXTI0		 (*(volatile uint32_t *)(0xE000E100))



void clock_init(){
	//enable clock for GPIOA
	RCC_APB2ENR |= (1<<2);

	//enable clock for AFIO
	RCC_APB2ENR |= (1<<0);

}

void GPIO_init(){

	GPIOA_CRH &=0xff0fffff;
	GPIOA_CRH |=0x00200000;
	GPIOA_CRL |=(1<<2);
}




int main(void)
{
	clock_init();
	GPIO_init();

	//enable EXTI0 configuration in PortA0
	AFIO_EXTICR1 = 0x0;

	//enable rising trigger
	EXTI_RTSR |= (1<<0);

	//enable EXTI line 0
	EXTI_IMR |= (1<<0);

	NVIC_EXTI0 |= (1<<6);

	while(1);
	return 0;
}



void EXTI0_IRQHandler(void){
	//interrupt has happened
	GPIOA_ODR ^= (1<<13);

	//clear Pending Interrupt Request for Line 0
	//otherwise the signal will stay 1 and the NVIC will keep sending the interrupt to the cpu
	EXTI_PR |= (1<<0);

}