#ifndef LED7_H
#define LED7_H

#include <stdint.h>
#include "stm32f1xx_hal.h"


typedef struct {
    GPIO_TypeDef *data_port;
    uint16_t D0_pin;
    uint16_t D1_pin;
    uint16_t D2_pin;
    uint16_t D3_pin;
    uint16_t D4_pin;
    uint16_t D5_pin;
    uint16_t D6_pin;
} LED7;

void LED7_Display(LED7 *led7, uint8_t num);

void input_num(LED7 *led7, uint8_t num);

#endif /* LED7_H */
