/*
 * Touch.c
 * 
 * Created: Mar 15, 2015
 *
 * Touch screen function 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>

#include "touch.h"

#define TS_ADCx_CLK_ENABLE()                  rcc_periph_clock_enable(RCC_ADC1)
#define TS_ADCx_GPIO_CLK_ENABLE()             rcc_periph_clock_enable(RCC_GPIOA)
#define TS_ADCx_GPIO_CLK_DISABLE()            rcc_periph_clock_disable(RCC_GPIOA)

#define TS_PIN_XP	GPIO10
#define TS_PIN_XM	GPIO4
#define TS_PIN_YP	GPIO1
#define TS_PIN_YM	GPIO8

#define TS_PORT_XP	GPIOB
#define TS_PORT_XM	GPIOA
#define TS_PORT_YP	GPIOA
#define TS_PORT_YM	GPIOA

#define TS_ADCCH_XM	ADC_CHANNEL4
#define TS_ADCCH_YP	ADC_CHANNEL1
#define TS_ADC_PORT	GPIOA
#define TS_ADC		ADC1


static void delay(volatile int i) {
	for(;i;--i);
}

/**
 * \brief Initializes ADC MSP. (MSP MCU Specific Package)
 * 
 * \param	None
 * 
 * \return void
 */
static void ADCx_MspInit(void) {
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  TS_ADCx_GPIO_CLK_ENABLE();
  
  /*** Configure the ADC peripheral ***/ 
  /* Enable ADC clock */
  TS_ADCx_CLK_ENABLE(); 
}

/**
 * \brief Initializes ADC
 * 
 * \param	None
 * 
 * \return void
 */
static void ADCx_Init(void) {

	adc_off(ADC1);
	adc_disable_scan_mode(ADC1);
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_15CYC);
	adc_power_on(ADC1);

//     /* ADC Config */
//     m_hNucleo_Adc.Instance                   = TS_ADC;
//     m_hNucleo_Adc.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4; /* (must not exceed 36MHz) */
//     m_hNucleo_Adc.Init.Resolution            = ADC_RESOLUTION12b;
//     m_hNucleo_Adc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
//     m_hNucleo_Adc.Init.ContinuousConvMode    = DISABLE;
//     m_hNucleo_Adc.Init.DiscontinuousConvMode = DISABLE;
//     m_hNucleo_Adc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
//     m_hNucleo_Adc.Init.EOCSelection          = EOC_SINGLE_CONV;
//     m_hNucleo_Adc.Init.NbrOfConversion       = 1;
//     m_hNucleo_Adc.Init.DMAContinuousRequests = DISABLE;    
}

/**
 * \brief Initializes the specified ADC channel
 * 
 * \param channel	Channel to initialize
 * 
 * \return uint8_t
 */
// static uint8_t ADCx_Channel_Init(uint16_t channel) {
// 	uint8_t status = 1;
// 
// 	uint8_t channel_array[31];
// 	channel_array[0] = channel;
// 	adc_set_regular_sequence(ADC1, 1, channel_array);
// // 	status = HAL_ADC_ConfigChannel(&m_hNucleo_Adc, &m_sConfig);
// 
// 	/* Return initialization status */
// 	return status;
// }

/**
 * \brief Sets the specified pin to analog mode
 * 
 * \param GPIOx		GPIO port
 * \param pin		GPIO pin
 * 
 * \return void
 */
static void GPIO_SetAnalog(uint32_t  GPIOx, uint16_t pin) {
	gpio_mode_setup(GPIOx, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, pin);
}

/**
 * \brief Sets the specified pin to output mode
 * 
 * \param GPIOx		GPIO port
 * \param pin		GPIO pin
 * 
 * \return void
 */
static void GPIO_SetOutput(uint32_t  GPIOx, uint16_t pin, int val) {
	gpio_mode_setup(GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
	if (val) {
		gpio_set(GPIOx, pin);
	} else {
		gpio_clear(GPIOx, pin);
	}
}

/**
 * \brief Sets the specified pin to input mode
 * 
 * \param GPIOx		GPIO port
 * \param pin		GPIO pin
 * 
 * \return void
 */
static uint16_t ADC_Measure(uint16_t ch) {
	uint8_t channel_array[31];
	channel_array[0] = ch;
	adc_set_regular_sequence(ADC1, 1, channel_array);
	adc_start_conversion_regular(ADC1);
	while (!adc_eoc(ADC1));
	uint16_t reg16 = adc_read_regular(ADC1);
	return reg16;
}

/**
 * \brief Touch initialization
 * 
 * \param	None
 * 
 * \return void
 */
void Touch_Begin(void) {
	ADCx_MspInit();
	ADCx_Init();
}

/**
 * \brief Gets the x-Coordinate raw value
 * 
 * \param	None
 * 
 * \return uint16_t		raw adc value
 */
uint16_t Touch_GetX(void)
{
	GPIO_SetAnalog(TS_PORT_YP, TS_PIN_YP);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 1);

	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 1);
	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 0);

	delay(100);

	uint32_t x = ADC_Measure(TS_ADCCH_YP);

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	return x;
}

/**
 * \brief Gets the y-Coordinate raw value
 * 
 * \param	none
 * 
 * \return uint16_t		raw adc value
 */
uint16_t Touch_GetY(void)
{
	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 1);
	GPIO_SetAnalog(TS_PORT_XM, TS_PIN_XM);

	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 0);
	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 1);

	delay(100);

	uint16_t y = ADC_Measure(TS_ADCCH_XM);

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	return y;
}
