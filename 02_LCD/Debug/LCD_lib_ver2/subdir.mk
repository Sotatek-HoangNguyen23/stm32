################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_lib_ver2/LCD.c 

OBJS += \
./LCD_lib_ver2/LCD.o 

C_DEPS += \
./LCD_lib_ver2/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
LCD_lib_ver2/%.o LCD_lib_ver2/%.su LCD_lib_ver2/%.cyclo: ../LCD_lib_ver2/%.c LCD_lib_ver2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/Work/Self/STM32/02_LCD/LCD_lib_ver2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LCD_lib_ver2

clean-LCD_lib_ver2:
	-$(RM) ./LCD_lib_ver2/LCD.cyclo ./LCD_lib_ver2/LCD.d ./LCD_lib_ver2/LCD.o ./LCD_lib_ver2/LCD.su

.PHONY: clean-LCD_lib_ver2

