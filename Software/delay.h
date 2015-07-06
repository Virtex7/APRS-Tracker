#ifndef DELAY_H_
#define DELAY_H_
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>

// #include "ff_test_term.h"

void sys_tick_handler(void);
void delayms(int millis);
void sys_tick_config(void);
#endif //--DELAY_H_