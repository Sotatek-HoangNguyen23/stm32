#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

// ===================== PRIVATE =====================

static void lcd_write_byte(uint8_t data)
{
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, 100);
}

static void lcd_pulse_enable(uint8_t data)
{
    lcd_write_byte(data | 0x04); // EN = 1
    HAL_Delay(1);
    lcd_write_byte(data & ~0x04); // EN = 0
    HAL_Delay(1);
}

static void lcd_send_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data = (nibble & 0xF0) | mode | 0x08;
    lcd_pulse_enable(data);
}

static void lcd_send_byte(uint8_t byte, uint8_t mode)
{
    lcd_send_nibble(byte & 0xF0, mode);
    lcd_send_nibble((byte << 4) & 0xF0, mode);
}

// ===================== PUBLIC =====================

void lcd_send_cmd(uint8_t cmd)
{
    lcd_send_byte(cmd, 0x00);
}

void lcd_send_data(uint8_t data)
{
    lcd_send_byte(data, 0x01);
}

void lcd_init(void)
{
    HAL_Delay(50);

    lcd_send_nibble(0x30, 0x00);
    HAL_Delay(5);
    lcd_send_nibble(0x30, 0x00);
    HAL_Delay(1);
    lcd_send_nibble(0x30, 0x00);
    HAL_Delay(10);

    lcd_send_nibble(0x20, 0x00);
    HAL_Delay(10);

    lcd_send_cmd(0x28);
    HAL_Delay(1);
    lcd_send_cmd(0x08);
    HAL_Delay(1);
    lcd_send_cmd(0x01);
    HAL_Delay(2);
    lcd_send_cmd(0x06);
    HAL_Delay(1);
    lcd_send_cmd(0x0C);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t row_addr[] = {0x00, 0x40, 0x14, 0x54};
    //                    ↑     ↑     ↑     ↑
    //                   row0  row1  row2  row3
    lcd_send_cmd(0x80 | (row_addr[row] + col));
}

void lcd_send_string(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}