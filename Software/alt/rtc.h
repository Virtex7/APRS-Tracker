#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/rcc.h>

uint32_t rtc_get_counter_val(void);
void rtc_set_counter_val(uint32_t counter_val);
void rtc_awake_from_off(enum rcc_osc clock_source);
void rtc_set_prescale_val(uint32_t prescale_val);

typedef struct {
	uint16_t year;	/* 1..4095 */
	uint8_t  month;	/* 1..12 */
	uint8_t  mday;	/* 1..31 */
	uint8_t  wday;	/* 0..6, Sunday = 0*/
	uint8_t  hour;	/* 0..23 */
	uint8_t  min;	/* 0..59 */
	uint8_t  sec;	/* 0..59 */
	uint8_t  dst;	/* 0 Winter, !=0 Summer */
} RTC_t;

int rtc_init(void);
bool rtc_gettime (RTC_t*);				/* Get time */
bool rtc_settime (const RTC_t*);		/* Set time */

#endif
