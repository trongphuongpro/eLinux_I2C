#ifndef __RTC_DS1307__
#define __RTC_DS1307__


#include <stdint.h>

extern const char *weekdays[];
extern const char *months[];

enum {SUCCESS=0, FAILED};

typedef struct datetime DateTime;

struct datetime {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t date;
	uint8_t month;
	uint16_t year;
};

int rtc_getTime(DateTime *);
int rtc_setTime(DateTime *);
void rtc_show(DateTime *);

#endif