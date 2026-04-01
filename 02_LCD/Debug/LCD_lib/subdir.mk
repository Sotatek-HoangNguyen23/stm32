################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_lib/LCD.c 

OBJS += \
./LCD_lib/LCD.o 

C_DEPS += \
./LCD_lib/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
LCD_lib/%.o LCD_lib/%.su LCD_lib/%.cyclo: ../LCD_lib/%.c LCD_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/Work/Self/STM32/02_LCD/LCD_lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LCD_lib

clean-LCD_lib:
	-$(RM) ./LCD_lib/LCD.cyclo ./LCD_lib/LCD.d ./LCD_lib/LCD.o ./LCD_lib/LCD.su

.PHONY: clean-LCD_lib

