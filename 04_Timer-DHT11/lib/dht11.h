#ifndef __DHT11_H
#define __DHT11_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "delay_us.h"

void SetInputPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void SetOutputPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint8_t DHT11_Start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint8_t DHT11_ReadData(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                       uint8_t *temperature, uint8_t *humidity);

#endif /* __DHT11_H */
