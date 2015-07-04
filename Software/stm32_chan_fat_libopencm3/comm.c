/* Martin Thomas 4/2009, 3/2010 */
#include <libopencm3/stm32/usart.h>
#include "comm.h"

#define USARTx USART1

int comm_test(void)
{
	return usart_get_flag(USARTx, USART_SR_RXNE);
}

char comm_get(void)
{
	return (char)usart_recv_blocking(USARTx);
}

void comm_put(char d)
{
	usart_send_blocking(USARTx, (uint16_t)d);
}

void comm_puts(const char* s)
{
	char c;
	while ( ( c = *s++) != '\0' ) {
		comm_put(c);
	}
}

void comm_init (void)
{
	// already done in main.c
}


