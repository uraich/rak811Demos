################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/stm32l1xx_hal_msp.c \
../Src/stm32l1xx_it.c \
../Src/syscalls.c \
../Src/system_stm32l1xx.c \
../Src/uart_io.c 

OBJS += \
./Src/main.o \
./Src/stm32l1xx_hal_msp.o \
./Src/stm32l1xx_it.o \
./Src/syscalls.o \
./Src/system_stm32l1xx.o \
./Src/uart_io.o 

C_DEPS += \
./Src/main.d \
./Src/stm32l1xx_hal_msp.d \
./Src/stm32l1xx_it.d \
./Src/syscalls.d \
./Src/system_stm32l1xx.d \
./Src/uart_io.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L151xBA -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Inc" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Inc/SX1276" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/STM32L1xx_HAL_Driver/Inc" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/STM32L1xx_HAL_Driver/Inc/Legacy" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/CMSIS/Device/ST/STM32L1xx/Include" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


