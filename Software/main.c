#include <stdio.h>
#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>


#include "st7783.h"
#include "touch.h"
#include "delay.h"
#include "usart.h"


void clock_setup(void);
void gpio_setup(void);


void clock_setup(void) {
	// High Speed internal oscillator wird auf die PLL gemappt
	// -> VOLLGAS!
	
	// Enable GPIOD clock für ALLE GPIOs.
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOD);
}


void gpio_setup(void) {
	// Set mode output und alternate function für externen USART2
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);
}




int main(void) {
	
	clock_setup();
	gpio_setup();
	usart_setup();
	
	printf("Willkommen!\r\n");
	
	LCD_Begin();
	LCD_SetRotation(0);
	LCD_FillScreen(BLACK);
	LCD_DrawFastHLine(0, 160, 240, RED);
	LCD_DrawCircle(120, 160, 100, BLUE);
	LCD_DrawRect(20, 40, 200, 240, WHITE);
	
// 	Touch_Begin();
	
	LCD_SetTextColor(GREEN, BLACK);
	LCD_SetTextSize(2);
	
	LCD_Printf("Guten Tag!");
	
	printf("Init abgeschlossen\r\n");
	
	
	// Infinite loop
	while (1) {
		;
	}
}