# STM32 Common APIs - Introduction

## Core / System
- `HAL_Init()` - Initialize HAL and SysTick
- `SystemClock_Config()` - Configure system clock
- `HAL_RCC_OscConfig()` - Configure oscillator
- `HAL_RCC_ClockConfig()` - Configure bus and CPU clocks

## GPIO
- `HAL_GPIO_Init()` - Configure GPIO pins
- `HAL_GPIO_WritePin()` - Set or reset a pin
- `HAL_GPIO_ReadPin()` - Read pin state
- `HAL_GPIO_TogglePin()` - Toggle output pin

## Delay / Time
- `HAL_Delay()` - Millisecond delay
- `HAL_GetTick()` - Current tick count

## UART
- `HAL_UART_Init()` - Initialize UART
- `HAL_UART_Transmit()` - Send data
- `HAL_UART_Receive()` - Receive data
- `HAL_UART_Transmit_IT()` - Send data by interrupt
- `HAL_UART_Receive_IT()` - Receive data by interrupt

## SPI
- `HAL_SPI_Init()` - Initialize SPI
- `HAL_SPI_Transmit()` - Send SPI data
- `HAL_SPI_Receive()` - Receive SPI data
- `HAL_SPI_TransmitReceive()` - Send and receive at the same time

## I2C
- `HAL_I2C_Init()` - Initialize I2C
- `HAL_I2C_Master_Transmit()` - Master write
- `HAL_I2C_Master_Receive()` - Master read
- `HAL_I2C_Mem_Write()` - Write to device register
- `HAL_I2C_Mem_Read()` - Read from device register

## Timer
- `HAL_TIM_Base_Init()` - Initialize timer base
- `HAL_TIM_Base_Start()` - Start timer
- `HAL_TIM_Base_Start_IT()` - Start timer with interrupt
- `HAL_TIM_PWM_Start()` - Start PWM output
- `HAL_TIM_PWM_Stop()` - Stop PWM output

## ADC
- `HAL_ADC_Init()` - Initialize ADC
- `HAL_ADC_Start()` - Start conversion
- `HAL_ADC_PollForConversion()` - Wait for conversion done
- `HAL_ADC_GetValue()` - Read conversion result

## DMA
- `HAL_DMA_Init()` - Initialize DMA
- `HAL_DMA_Start()` - Start DMA transfer
- `HAL_DMA_Start_IT()` - Start DMA transfer with interrupt

## Interrupt / NVIC
- `HAL_NVIC_SetPriority()` - Set interrupt priority
- `HAL_NVIC_EnableIRQ()` - Enable interrupt line
- `HAL_NVIC_DisableIRQ()` - Disable interrupt line

## Flash / Power
- `HAL_FLASH_Unlock()` - Unlock flash for write
- `HAL_FLASH_Lock()` - Lock flash again
- `HAL_FLASH_Program()` - Program flash memory
- `HAL_PWR_EnterSTOPMode()` - Enter low-power stop mode

## Common Macros
- `GPIO_PIN_SET` - High level
- `GPIO_PIN_RESET` - Low level
- `GPIO_PIN_x` - Pin mask
- `GPIO_MODE_OUTPUT_PP` - Push-pull output
- `GPIO_NOPULL` - No pull-up / pull-down
- `GPIO_SPEED_FREQ_LOW` - Low GPIO speed
