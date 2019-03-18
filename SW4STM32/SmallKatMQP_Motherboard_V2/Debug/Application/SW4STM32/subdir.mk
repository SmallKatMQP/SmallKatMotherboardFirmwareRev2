################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
/home/kbisland/SmallKatMQP_Motherboard_V2/SW4STM32/startup_stm32h753xx.s 

OBJS += \
./Application/SW4STM32/startup_stm32h753xx.o 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32h753xx.o: /home/kbisland/SmallKatMQP_Motherboard_V2/SW4STM32/startup_stm32h753xx.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


