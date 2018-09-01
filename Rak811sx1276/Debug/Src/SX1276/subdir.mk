################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SX1276/sx1276-board.c \
../Src/SX1276/sx1276.c 

OBJS += \
./Src/SX1276/sx1276-board.o \
./Src/SX1276/sx1276.o 

C_DEPS += \
./Src/SX1276/sx1276-board.d \
./Src/SX1276/sx1276.d 


# Each subdirectory must supply rules for building sources it contributes
Src/SX1276/%.o: ../Src/SX1276/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L151xBA -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Inc" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Inc/SX1276" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/STM32L1xx_HAL_Driver/Inc" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/STM32L1xx_HAL_Driver/Inc/Legacy" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/CMSIS/Device/ST/STM32L1xx/Include" -I"/opt/ucc/projects/cow/code/STM32CubeMX/Rak811sx1276/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


