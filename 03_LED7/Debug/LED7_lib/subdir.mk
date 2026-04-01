################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LED7_lib/LED7.c 

OBJS += \
./LED7_lib/LED7.o 

C_DEPS += \
./LED7_lib/LED7.d 


# Each subdirectory must supply rules for building sources it contributes
LED7_lib/%.o LED7_lib/%.su LED7_lib/%.cyclo: ../LED7_lib/%.c LED7_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/Work/Self/STM32/03_LED7/LED7_lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LED7_lib

clean-LED7_lib:
	-$(RM) ./LED7_lib/LED7.cyclo ./LED7_lib/LED7.d ./LED7_lib/LED7.o ./LED7_lib/LED7.su

.PHONY: clean-LED7_lib

