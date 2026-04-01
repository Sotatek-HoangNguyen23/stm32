#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

#define MDATA 0x01
#define MCMD  0x00

typedef struct {
	GPIO_TypeDef *data_port;
	GPIO_TypeDef *r_port;
	uint16_t D0_pin;
	uint16_t D1_pin;
	uint16_t D2_pin;
	uint16_t D3_pin;
	uint16_t D4_pin;
	uint16_t D5_pin;
	uint16_t D6_pin;
	uint16_t D7_pin;
	uint16_t RS_pin;
	uint16_t RW_pin;
	uint16_t E_pin;
} LCD;

void LCD_Write_Byte(LCD *lcd, uint8_t data, uint8_t mode);

void LCD_Write_Data(LCD *lcd, uint8_t data);

void LCD_Write_Command(LCD *lcd, uint8_t data);

void LCD_Print(LCD *lcd, char *str);

void LCD_init(LCD *lcd);

#endif /* LCD_H */