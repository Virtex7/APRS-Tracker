/*******************************************************************************
* File Name          : main.c
* Author             : Martin Thomas, main-skeleton based on code from the
*                      STMicroelectronics MCD Application Team
* Version            : see VERSION_STRING below
* Date               : see VERSION_STRING below
* Description        : Main program body for the SD-Card tests
********************************************************************************
* License: 3BSD
*******************************************************************************/

#define VERSION_STRING "V1.2.1 7/2010"

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/dispatch/nvic.h>
#include <libopencm3/cm3/systick.h>
#include "main.h"
#include "comm.h"
#include "rtc.h"
#include "diskio.h" /* disk_timerproc */
#include "ff_test_term.h"


/* Private typedef -----------------------------------------------------------*/
typedef enum { APPSTATE_FF_TERM, APPSTATE_TESTMENU } AppState;

/* Private variables ---------------------------------------------------------*/
const char welcome[] = "\r\nHello from a STM32 Demo-Application, M. Thomas\r\n" VERSION_STRING"\r\n";
const char gimmick[] =
"  _____ _______ __  __ ____ ___  ______ __  ___\r\n"\
" / ____|__   __|  \\/  |___ \\__ \\|  ____/_ |/ _ \\\r\n"\
"| (___    | |  | \\  / | __) | ) | |__   | | | | |_  __\r\n"\
" \\___ \\   | |  | |\\/| ||__ < / /|  __|  | | | | \\ \\/ /\r\n"\
" ____) |  | |  | |  | |___) / /_| |     | | |_| |>  <\r\n"\
"|_____/   |_|  |_|  |_|____/____|_|     |_|\\___//_/\\_\\\r\n";


/* Private function prototypes -----------------------------------------------*/
void Periph_Configuration(void);
void GPIO_Configuration(void);
void usart_setup(void);
void SysTick_Config(void);

/* Public functions -- -------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main_systick_action
* Description    : operations to be done every 1ms
* Input          : None
* Output         : None
* Return         : None
*  overrides weak SysTick_Handler in startup_stm32*.c
*  When a RAMFUNC every function called from inside the ISR must be
*  reachable. This can be achieved by using compiler-option -mlong-calls
*  which globally enables long-calls. Here this option has not been used
*  instead the unreachable functions GPIO_Set/ResetBits have been replaced
*  by direct register-writes and disk_timerproc has also been attributed
*  as RAMFUNC to be reachable.
*******************************************************************************/
void sys_tick_handler(void)
{
	static uint16_t cnt=0;
	static uint8_t cntdiskio=0;

	cnt++;
	if( cnt >= 500 ) {
		cnt = 0;
		/* alive sign */
		gpio_toggle(GPIOB,GPIO9);
	}

	cntdiskio++;
	if ( cntdiskio >= 10 ) {
		cntdiskio = 0;
		disk_timerproc(); /* to be called every 10ms */
	}

	ff_test_term_timerproc(); /* to be called every ms */
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	AppState appState = APPSTATE_FF_TERM;

	/* System Clocks Configuration */
	Periph_Configuration();

	/* Configure the GPIO ports */
	GPIO_Configuration();

	/* Turn on/off LED(s) */
	gpio_set(GPIOB,GPIO8);

	/* Setup SysTick Timer for 1 millisecond interrupts, also enables Systick and Systick-Interrupt */
	SysTick_Config();

	usart_setup();

	comm_puts(welcome);
	comm_puts(gimmick);

	while (1) ff_test_term();
}

/*--------------------------------------------------------------------------*/
/** @brief USART Setup

USART 1 is configured for 115200 baud, no flow control, and (no) interrupt.
*/

void usart_setup(void)
{
/* Enable clocks for GPIO port A (for GPIO_USART1_TX) and USART1. */
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPAEN |
				    RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN);
/* Enable the USART1 interrupt. */
//	nvic_enable_irq(NVIC_USART1_IRQ);
/* Setup GPIO pin GPIO_USART1_RE_TX on GPIO port A for transmit. */
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
/* Setup GPIO pin GPIO_USART1_RE_RX on GPIO port A for receive. */
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT,
		      GPIO_CNF_INPUT_FLOAT, GPIO_USART1_RX);
/* Setup UART parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART1, USART_MODE_TX_RX);
/* Enable USART1 receive interrupts. */
//	usart_enable_rx_interrupt(USART1);
//	usart_disable_tx_interrupt(USART1);
/* Finally enable the USART. */
	usart_enable(USART1);
}

/*******************************************************************************
* Function Name  : PeriphConfiguration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Periph_Configuration(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
/* Enable GPIO clocks and LED ports. */
    rcc_peripheral_enable_clock(&RCC_APB2ENR,
                RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
			    GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
/* Enable DMA clock */
	rcc_peripheral_enable_clock(&RCC_AHBENR, RCC_AHBENR_DMA1EN);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
}

void SysTick_Config()
{
	/* 72MHz / 8 => 9,000,000 counts per second */
	systick_set_clocksource(STK_CTRL_CLKSOURCE_AHB_DIV8);

	/* 9000000/9000 = 1000 overflows per second - every 1ms one interrupt */
	/* SysTick interrupt every N clock pulses: set reload to N-1 */
	systick_set_reload(8999);

	systick_interrupt_enable();

	/* Start counting. */
	systick_counter_enable();
}


