#include "LCD.h"

void LCD_Write_Byte(LCD *lcd, uint8_t data, uint8_t mode) {
	if (mode == 0x01) {
		HAL_GPIO_WritePin(lcd->r_port, lcd->RS_pin, 1);
	} else if (mode == 0x00) {
		HAL_GPIO_WritePin(lcd->r_port, lcd->RS_pin, 0);
	}

	HAL_GPIO_WritePin(lcd->data_port, lcd->D0_pin, (data & 0x01) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D1_pin, (data & 0x02) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D2_pin, (data & 0x04) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D3_pin, (data & 0x08) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D4_pin, (data & 0x10) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D5_pin, (data & 0x20) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D6_pin, (data & 0x40) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->data_port, lcd->D7_pin, (data & 0x80) ? 1 : 0);

	HAL_GPIO_WritePin(lcd->r_port, lcd->E_pin, 0);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->r_port, lcd->E_pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->r_port, lcd->E_pin, 0);
	HAL_Delay(1);
}

void LCD_Write_Data(LCD *lcd, uint8_t data) {
	LCD_Write_Byte(lcd, data, 1);
}

void LCD_Write_Command(LCD *lcd, uint8_t data) {
	LCD_Write_Byte(lcd, data, 0);
}

void LCD_Print(LCD *lcd, char *str) {
	while (*str) {
		LCD_Write_Data(lcd, *str++);
	}
}

void LCD_init(LCD *lcd) {
    HAL_GPIO_WritePin(lcd->r_port, lcd->RW_pin, 0);
	HAL_Delay(50);
	LCD_Write_Command(lcd, 0x38);
	HAL_Delay(5);
	LCD_Write_Command(lcd, 0x0C);
	HAL_Delay(5);
	LCD_Write_Command(lcd, 0x01);
}