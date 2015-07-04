#include "delay.h"

volatile int milliseconds = 0;
void sys_tick_handler(void) {
	milliseconds++;
}

// ACHTUNG:  gehe davon aus, dass es systick eine ms dauert!
void delayms(int millis) {
	int temp = milliseconds;
	while (temp+millis != milliseconds) {}
}

void sys_tick_config(void){
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB); // CPU-Frequenz = 16MHz bei internem Oszillator
	systick_set_reload(83999);
	systick_interrupt_enable();
	systick_counter_enable();
}