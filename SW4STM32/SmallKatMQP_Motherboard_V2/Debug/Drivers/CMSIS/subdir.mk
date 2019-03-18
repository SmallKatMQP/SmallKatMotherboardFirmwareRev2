################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/system_stm32h7xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32h7xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32h7xx.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/system_stm32h7xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


