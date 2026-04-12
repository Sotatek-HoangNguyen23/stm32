#include "rtc_sync.h"

static uint8_t rtc_parse_dec2(const char *text)
{
    return (uint8_t)((text[0] - '0') * 10U + (text[1] - '0'));
}

static uint8_t rtc_month_from_name(const char *month)
{
    if (month[0] == 'J' && month[1] == 'a' && month[2] == 'n') return 1;
    if (month[0] == 'F' && month[1] == 'e' && month[2] == 'b') return 2;
    if (month[0] == 'M' && month[1] == 'a' && month[2] == 'r') return 3;
    if (month[0] == 'A' && month[1] == 'p' && month[2] == 'r') return 4;
    if (month[0] == 'M' && month[1] == 'a' && month[2] == 'y') return 5;
    if (month[0] == 'J' && month[1] == 'u' && month[2] == 'n') return 6;
    if (month[0] == 'J' && month[1] == 'u' && month[2] == 'l') return 7;
    if (month[0] == 'A' && month[1] == 'u' && month[2] == 'g') return 8;
    if (month[0] == 'S' && month[1] == 'e' && month[2] == 'p') return 9;
    if (month[0] == 'O' && month[1] == 'c' && month[2] == 't') return 10;
    if (month[0] == 'N' && month[1] == 'o' && month[2] == 'v') return 11;
    if (month[0] == 'D' && month[1] == 'e' && month[2] == 'c') return 12;
    return 1;
}

static uint8_t rtc_is_leap_year(uint16_t full_year)
{
    return (uint8_t)(((full_year % 4U) == 0U && (full_year % 100U) != 0U) || ((full_year % 400U) == 0U));
}

static uint8_t rtc_days_in_month(uint8_t month, uint16_t full_year)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return rtc_is_leap_year(full_year) ? 29 : 28;
    default:
        return 30;
    }
}

static uint8_t rtc_day_of_week(uint16_t full_year, uint8_t month, uint8_t date)
{
    static const uint8_t offsets[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    uint16_t year = full_year;

    if (month < 3U)
    {
        year -= 1U;
    }

    return (uint8_t)(((year + year / 4U - year / 100U + year / 400U + offsets[month - 1U] + date) % 7U) + 1U);
}

static uint32_t rtc_to_seconds(const DS1307_Time *time)
{
    uint16_t full_year = (uint16_t)(2000U + time->year);
    uint32_t days = 0;

    for (uint16_t year = 2000U; year < full_year; ++year)
    {
        days += 365U + rtc_is_leap_year(year);
    }

    for (uint8_t month = 1U; month < time->month; ++month)
    {
        days += rtc_days_in_month(month, full_year);
    }

    days += (uint32_t)(time->date - 1U);

    return (days * 86400UL) + ((uint32_t)time->hours * 3600UL) + ((uint32_t)time->minutes * 60UL) + time->seconds;
}

static uint8_t rtc_is_valid(const DS1307_Time *time)
{
    uint16_t full_year = (uint16_t)(2000U + time->year);

    if (time->seconds > 59U) return 0U;
    if (time->minutes > 59U) return 0U;
    if (time->hours > 23U) return 0U;
    if (time->month < 1U || time->month > 12U) return 0U;
    if (time->date < 1U || time->date > rtc_days_in_month(time->month, full_year)) return 0U;
    if (time->day < 1U || time->day > 7U) return 0U;

    return 1U;
}

static uint32_t rtc_abs_diff_seconds(const DS1307_Time *a, const DS1307_Time *b)
{
    uint32_t sa = rtc_to_seconds(a);
    uint32_t sb = rtc_to_seconds(b);
    return (sa >= sb) ? (sa - sb) : (sb - sa);
}

static void rtc_get_build_time(DS1307_Time *time)
{
    const char *build_date = __DATE__;
    const char *build_time = __TIME__;
    uint16_t full_year = (uint16_t)((build_date[7] - '0') * 1000U + (build_date[8] - '0') * 100U +
                                    (build_date[9] - '0') * 10U + (build_date[10] - '0'));

    time->month = rtc_month_from_name(build_date);
    time->date = (build_date[4] == ' ') ? (uint8_t)(build_date[5] - '0') : rtc_parse_dec2(&build_date[4]);
    time->year = (uint8_t)(full_year - 2000U);
    time->hours = rtc_parse_dec2(&build_time[0]);
    time->minutes = rtc_parse_dec2(&build_time[3]);
    time->seconds = rtc_parse_dec2(&build_time[6]);
    time->day = rtc_day_of_week(full_year, time->month, time->date);
}

void rtc_sync_from_build_time(DS1307_Time *current_time, uint32_t tolerance_seconds)
{
    DS1307_Time rtc_time;
    DS1307_Time pc_time;
    uint32_t rtc_seconds;
    uint32_t pc_seconds;
    uint32_t diff;

    ds1307_get_time(&rtc_time);
    rtc_get_build_time(&pc_time);

    if (!rtc_is_valid(&rtc_time))
    {
        ds1307_set_time(pc_time.hours, pc_time.minutes, pc_time.seconds,
                        pc_time.day, pc_time.date, pc_time.month, pc_time.year);
        *current_time = pc_time;
        return;
    }

    rtc_seconds = rtc_to_seconds(&rtc_time);
    pc_seconds = rtc_to_seconds(&pc_time);
    diff = rtc_abs_diff_seconds(&rtc_time, &pc_time);

    /* Avoid writing older build timestamp back into RTC. */
    if (rtc_seconds > pc_seconds)
    {
        *current_time = rtc_time;
        return;
    }

    if (diff > tolerance_seconds)
    {
        ds1307_set_time(pc_time.hours, pc_time.minutes, pc_time.seconds,
                        pc_time.day, pc_time.date, pc_time.month, pc_time.year);
        *current_time = pc_time;
    }
    else
    {
        *current_time = rtc_time;
    }
}
