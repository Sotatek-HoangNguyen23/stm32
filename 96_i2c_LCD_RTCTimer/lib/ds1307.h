#ifndef DS1307_H
#define DS1307_H

#include "stm32f1xx_hal.h"

// ===================== ADDRESS =====================
#define DS1307_ADDR  (0x68 << 1)  // = 0xD0

// ===================== REGISTER =====================
#define DS1307_REG_SECONDS  0x00
#define DS1307_REG_MINUTES  0x01
#define DS1307_REG_HOURS    0x02
#define DS1307_REG_DAY      0x03
#define DS1307_REG_DATE     0x04
#define DS1307_REG_MONTH    0x05
#define DS1307_REG_YEAR     0x06
#define DS1307_REG_CONTROL  0x07
#define DS1307_REG_RAM      0x08

// ===================== STRUCT =====================
typedef struct {
    uint8_t seconds;  // 0-59
    uint8_t minutes;  // 0-59
    uint8_t hours;    // 0-23
    uint8_t day;      // 1-7
    uint8_t date;     // 1-31
    uint8_t month;    // 1-12
    uint8_t year;     // 0-99
} DS1307_Time;

// ===================== FUNCTIONS =====================
void    ds1307_start(void);
void    ds1307_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds,
                        uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void    ds1307_read_all(void);
void    ds1307_get_time(DS1307_Time *t);

// RAM
void    ds1307_write_ram(uint8_t addr, uint8_t *data, uint8_t size);
void    ds1307_read_ram(uint8_t addr, uint8_t *data, uint8_t size);

#endif