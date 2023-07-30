#include "stdio.h"
#include "stdint.h"
#define RCC 0x40021000
#define GPIOA 0x40010800
#define RCC_APB2ENR *(volatile uint32_t *) (RCC + 0x18)
#define GPIOA_CRH *(volatile uint32_t *) (GPIOA + 0x04)
#define GPIOA_ODR *(volatile uint32_t *) (GPIOA + 0x0C)
char ggs[]={"gg"};
int const ggs_int[]={1,2,3};
int x;

typedef union {
    volatile uint32_t all;
    struct
    {
        volatile uint16_t reserved :13;
        volatile uint16_t pin13 :1;
    } Pin;
    
} R_ODR_t;

volatile R_ODR_t *R_ODR = (volatile R_ODR_t*)(GPIOA+0x0C);

int main()
{
    RCC_APB2ENR |= (1<<2);
    GPIOA_CRH &= 0XFF0FFFFF;
    GPIOA_CRH |= 0X00200000;
    while (1)
    {
        int i;
        R_ODR->Pin.pin13=1;
        for (i = 0; i < 5000; i++);
        R_ODR->Pin.pin13=0;
        for (i = 0; i < 5000; i++);

    }
    

}
