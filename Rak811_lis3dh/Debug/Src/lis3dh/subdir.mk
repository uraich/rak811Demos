################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lis3dh/lis3dh.c \
../Src/lis3dh/lis3dhDebug.c \
../Src/lis3dh/test.c 

OBJS += \
./Src/lis3dh/lis3dh.o \
./Src/lis3dh/lis3dhDebug.o \
./Src/lis3dh/test.o 

C_DEPS += \
./Src/lis3dh/lis3dh.d \
./Src/lis3dh/lis3dhDebug.d \
./Src/lis3dh/test.d 


# Each subdirectory must supply rules for building sources it contributes
Src/lis3dh/%.o: ../Src/lis3dh/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L151xB -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811_lis3dh/Inc" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811_lis3dh/Drivers/STM32L1xx_HAL_Driver/Inc" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811_lis3dh/Drivers/STM32L1xx_HAL_Driver/Inc/Legacy" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811_lis3dh/Drivers/CMSIS/Device/ST/STM32L1xx/Include" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811_lis3dh/Drivers/CMSIS/Include" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811_lis3dh/Inc/lis3dh"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


