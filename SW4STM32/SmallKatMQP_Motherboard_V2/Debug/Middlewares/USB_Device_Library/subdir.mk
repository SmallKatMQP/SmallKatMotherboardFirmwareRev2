################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c \
/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/USB_Device_Library/usbd_core.o \
./Middlewares/USB_Device_Library/usbd_ctlreq.o \
./Middlewares/USB_Device_Library/usbd_customhid.o \
./Middlewares/USB_Device_Library/usbd_ioreq.o 

C_DEPS += \
./Middlewares/USB_Device_Library/usbd_core.d \
./Middlewares/USB_Device_Library/usbd_ctlreq.d \
./Middlewares/USB_Device_Library/usbd_customhid.d \
./Middlewares/USB_Device_Library/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USB_Device_Library/usbd_core.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_ctlreq.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_customhid.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_ioreq.o: /home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H753xx -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Drivers/CMSIS/Include" -I"/home/kbisland/SmallKatMQP_Motherboard_V2/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


