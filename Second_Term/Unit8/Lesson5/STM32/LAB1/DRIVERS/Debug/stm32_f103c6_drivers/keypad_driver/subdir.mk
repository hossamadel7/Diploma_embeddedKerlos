################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_drivers/keypad_driver/keypad.c 

OBJS += \
./stm32_f103c6_drivers/keypad_driver/keypad.o 

C_DEPS += \
./stm32_f103c6_drivers/keypad_driver/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_drivers/keypad_driver/keypad.o: ../stm32_f103c6_drivers/keypad_driver/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/KH/STM32CubeIDE/DRIVERS/stm32_f103c6_drivers/inc" -I"C:/Users/KH/STM32CubeIDE/DRIVERS/stm32_f103c6_drivers/keypad_driver" -I"C:/Users/KH/STM32CubeIDE/DRIVERS/stm32_f103c6_drivers/lcd_driver" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_drivers/keypad_driver/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

