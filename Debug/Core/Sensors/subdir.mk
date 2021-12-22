################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Sensors/compass.c \
../Core/Sensors/temperature.c 

OBJS += \
./Core/Sensors/compass.o \
./Core/Sensors/temperature.o 

C_DEPS += \
./Core/Sensors/compass.d \
./Core/Sensors/temperature.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Sensors/%.o: ../Core/Sensors/%.c Core/Sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F303x8 -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=8000000 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Sensors

clean-Core-2f-Sensors:
	-$(RM) ./Core/Sensors/compass.d ./Core/Sensors/compass.o ./Core/Sensors/temperature.d ./Core/Sensors/temperature.o

.PHONY: clean-Core-2f-Sensors

