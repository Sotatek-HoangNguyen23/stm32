#include "LED7.h"

static const uint8_t seg_map[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void LED7_Display(LED7 *led7, uint8_t num) {
    if (led7 == NULL) {
        return;
    }

    if (num > 9) {
        num = 0;
    }

    uint8_t segments = seg_map[num];
    
    HAL_GPIO_WritePin(led7->data_port, led7->D0_pin, (segments & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led7->data_port, led7->D1_pin, (segments & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led7->data_port, led7->D2_pin, (segments & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led7->data_port, led7->D3_pin, (segments & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led7->data_port, led7->D4_pin, (segments & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led7->data_port, led7->D5_pin, (segments & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led7->data_port, led7->D6_pin, (segments & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}   

void input_num(LED7 *led7, uint8_t num) {
    LED7_Display(led7, num);
}