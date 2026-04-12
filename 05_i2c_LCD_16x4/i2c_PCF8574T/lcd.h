#ifndef LCD_H
#define LCD_H

#include "stm32f1xx_hal.h"

#define LCD_ADDR 0x4E 

void lcd_init(void);

void lcd_send_cmd(uint8_t cmd);

void lcd_send_data(uint8_t data);

void lcd_send_string(char *str);

void lcd_set_cursor(uint8_t row, uint8_t col);

void lcd_clear(void);

#endif /* LCD_H */