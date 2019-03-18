################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/main.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/stm32h7xx_hal_msp.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/stm32h7xx_it.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/usb_device.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/usbd_conf.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/usbd_custom_hid_if.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Src/usbd_desc.c 

OBJS += \
./Application/User/main.o \
./Application/User/stm32h7xx_hal_msp.o \
./Application/User/stm32h7xx_it.o \
./Application/User/usb_device.o \
./Application/User/usbd_conf.o \
./Application/User/usbd_custom_hid_if.o \
./Application/User/usbd_desc.o 

C_DEPS += \
./Application/User/main.d \
./Application/User/stm32h7xx_hal_msp.d \
./Application/User/stm32h7xx_it.d \
./Application/User/usb_device.d \
./Application/User/usbd_conf.d \
./Application/User/usbd_custom_hid_if.d \
./Application/User/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/main.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32h7xx_hal_msp.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/stm32h7xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32h7xx_it.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/stm32h7xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usb_device.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/usb_device.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_conf.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/usbd_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_custom_hid_if.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/usbd_custom_hid_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_desc.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Src/usbd_desc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


