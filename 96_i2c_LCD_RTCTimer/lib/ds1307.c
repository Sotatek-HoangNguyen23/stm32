#include "ds1307.h"

extern I2C_HandleTypeDef hi2c2;

// ===================== PRIVATE =====================

static uint8_t dec_to_bcd(uint8_t dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

static uint8_t bcd_to_dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// ===================== PUBLIC =====================

void ds1307_start(void)
{
    uint8_t seconds;

    HAL_I2C_Mem_Read(&hi2c2, DS1307_ADDR,
                     DS1307_REG_SECONDS, I2C_MEMADD_SIZE_8BIT,
                     &seconds, 1, 100);

    seconds &= ~(1 << 7);  // clear CH bit

    HAL_I2C_Mem_Write(&hi2c2, DS1307_ADDR,
                      DS1307_REG_SECONDS, I2C_MEMADD_SIZE_8BIT,
                      &seconds, 1, 100);
}

void ds1307_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds,
                     uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
    uint8_t buf[7];

    buf[0] = dec_to_bcd(seconds) & ~(1 << 7); // CH=0
    buf[1] = dec_to_bcd(minutes);
    buf[2] = dec_to_bcd(hours)   & ~(1 << 6); // 24h mode
    buf[3] = dec_to_bcd(day);
    buf[4] = dec_to_bcd(date);
    buf[5] = dec_to_bcd(month);
    buf[6] = dec_to_bcd(year);

    HAL_I2C_Mem_Write(&hi2c2, DS1307_ADDR,
                      DS1307_REG_SECONDS, I2C_MEMADD_SIZE_8BIT,
                      buf, 7, 100);
}

void ds1307_read_all(void)
{
    extern uint8_t data[7];

    HAL_I2C_Mem_Read(&hi2c2, DS1307_ADDR,
                     DS1307_REG_SECONDS, I2C_MEMADD_SIZE_8BIT,
                     data, 7, 100);
}

void ds1307_get_time(DS1307_Time *t)
{
    uint8_t buf[7];

    HAL_I2C_Mem_Read(&hi2c2, DS1307_ADDR,
                     DS1307_REG_SECONDS, I2C_MEMADD_SIZE_8BIT,
                     buf, 7, 100);

    t->seconds = bcd_to_dec(buf[0] & 0x7F); // mask CH bit
    t->minutes = bcd_to_dec(buf[1]);
    t->hours   = bcd_to_dec(buf[2] & 0x3F); // mask 12/24 bit
    t->day     = bcd_to_dec(buf[3]);
    t->date    = bcd_to_dec(buf[4]);
    t->month   = bcd_to_dec(buf[5]);
    t->year    = bcd_to_dec(buf[6]);
}

// ===================== RAM =====================

void ds1307_write_ram(uint8_t addr, uint8_t *data, uint8_t size)
{
    // addr hợp lệ: 0x08 - 0x3F
    if (addr < DS1307_REG_RAM || addr > 0x3F) return;

    HAL_I2C_Mem_Write(&hi2c2, DS1307_ADDR,
                      addr, I2C_MEMADD_SIZE_8BIT,
                      data, size, 100);
}

void ds1307_read_ram(uint8_t addr, uint8_t *data, uint8_t size)
{
    // addr hợp lệ: 0x08 - 0x3F
    if (addr < DS1307_REG_RAM || addr > 0x3F) return;

    HAL_I2C_Mem_Read(&hi2c2, DS1307_ADDR,
                     addr, I2C_MEMADD_SIZE_8BIT,
                     data, size, 100);
}