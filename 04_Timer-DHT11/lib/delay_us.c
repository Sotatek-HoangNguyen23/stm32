#include "delay_us.h"

extern TIM_HandleTypeDef htim1;

void delay_us(uint16_t us)
{
  uint16_t start = __HAL_TIM_GET_COUNTER(&htim1);

  if ((htim1.Instance->CR1 & TIM_CR1_CEN) == 0U)
  {
    HAL_TIM_Base_Start(&htim1);
    start = __HAL_TIM_GET_COUNTER(&htim1);
  }

  while ((uint16_t)(__HAL_TIM_GET_COUNTER(&htim1) - start) < us)
  {
  }
}