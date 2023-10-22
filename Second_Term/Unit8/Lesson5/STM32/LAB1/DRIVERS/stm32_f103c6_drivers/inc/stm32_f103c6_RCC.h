
#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_

#include "STM32F103x6.h"

#define HSI_CLK (uint32_t)8000000
#define HSE_CLK (uint32_t)16000000


uint32_t MCAL_RCC_GetSYSCLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
