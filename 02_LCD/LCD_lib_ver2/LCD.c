#include "LCD.h"

void LCD_Write_Byte(LCD *lcd, uint8_t data, uint8_t mode) {
	HAL_GPIO_WritePin(lcd->r_port, lcd->RS_pin,
			(mode == MDATA) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcd->data_port, lcd->D0_pin,
			(data & 0x01U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D1_pin,
			(data & 0x02U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D2_pin,
			(data & 0x04U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D3_pin,
			(data & 0x08U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D4_pin,
			(data & 0x10U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D5_pin,
			(data & 0x20U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D6_pin,
			(data & 0x40U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D7_pin,
			(data & 0x80U) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcd->r_port, lcd->E_pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->r_port, lcd->E_pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void LCD_Print(LCD *lcd, const char *str) {
	while (*str) {
		LCD_Write_Byte(lcd, (uint8_t)*str++, MDATA);
	}
}

void LCD_init(LCD *lcd) {
	HAL_GPIO_WritePin(lcd->r_port, lcd->RW_pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	LCD_Write_Byte(lcd, 0x38, MCMD);
	HAL_Delay(5);
	LCD_Write_Byte(lcd, 0x0C, MCMD);
	HAL_Delay(5);
	LCD_Write_Byte(lcd, 0x01, MCMD);
	HAL_Delay(5);
}
