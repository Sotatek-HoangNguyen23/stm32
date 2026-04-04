#include "dht11.h"

void SetInputPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void SetOutputPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

uint8_t DHT11_Start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint32_t timeout;

    SetOutputPin(GPIOx, GPIO_Pin);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(18);

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
    delay_us(30);

    SetInputPin(GPIOx, GPIO_Pin);

    timeout = 0;
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
    {
        if (++timeout > 10000)
            return 0;
    }

    timeout = 0;
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
    {
        if (++timeout > 10000)
            return 0;
    }

    timeout = 0;
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
    {
        if (++timeout > 10000)
            return 0;
    }

    return 1;
}

uint8_t DHT11_ReadData(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                       uint8_t *temperature, uint8_t *humidity)
{
    uint8_t data[5] = {0};
    uint32_t timeout;

    if (temperature == NULL || humidity == NULL)
        return 0;

    if (!DHT11_Start(GPIOx, GPIO_Pin))
        return 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            timeout = 0;
            while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
            {
                if (++timeout > 10000)
                    return 0;
            }

            delay_us(40);

            if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
            {
                data[i] |= (1 << (7 - j));
            }

            timeout = 0;
            while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
            {
                if (++timeout > 10000)
                    return 0;
            }
        }
    }

    if (data[4] != (data[0] + data[1] + data[2] + data[3]))
        return 0;

    *humidity = data[0];
    *temperature = data[2];

    return 1;
}