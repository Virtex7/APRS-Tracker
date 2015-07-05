#include "delay.h"

volatile int milliseconds = 0;
void sys_tick_handler(void) {
	milliseconds++;
	static uint16_t cnt=0;
	static uint8_t cntdiskio=0;
	
	// Für die SD-Karte und den Dateizugriff
	cntdiskio++;
	if ( cntdiskio >= 10 ) {
		cntdiskio = 0;
		disk_timerproc(); /* to be called every 10ms */
	}
	
	ff_test_term_timerproc(); /* to be called every ms */
}

// ACHTUNG:  gehe davon aus, dass es systick eine ms dauert!
void delayms(int millis) {
	int temp = milliseconds;
	while (temp+millis != milliseconds) {}
}

void sys_tick_config(void){
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB); // CPU-Frequenz = 16MHz bei internem Oszillator
	systick_set_reload(15999);
	systick_interrupt_enable();
	systick_counter_enable();
}