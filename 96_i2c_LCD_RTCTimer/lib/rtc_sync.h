#ifndef RTC_SYNC_H
#define RTC_SYNC_H

#include "ds1307.h"

void rtc_sync_from_build_time(DS1307_Time *current_time, uint32_t tolerance_seconds);

#endif
