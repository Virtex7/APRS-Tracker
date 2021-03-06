#include "usart.h"

// #define BUFLEN 127
// 
// static uint16_t start_ndx;
// static uint16_t end_ndx;
// static char buf[BUFLEN+1];
// #define buf_len ((end_ndx - start_ndx) % BUFLEN)
// static inline int inc_ndx(int n) { return ((n + 1) % BUFLEN); }
// static inline int dec_ndx(int n) { return (((n + BUFLEN) - 1) % BUFLEN); }

/* Martin Thomas 4/2009, 3/2010 */

#define USARTx USART2

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

// Codeteil ab hier von Philipp Hörauf

void usart_clock_setup(void){
	rcc_periph_clock_enable(RCC_USART2);
}

void usart_setup(void) {
	usart_clock_setup();
	// RX an PA3, TX an PA2
	
	/* Setup USART2 parameters. */
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART2);
}


// /* back up the cursor one space */
// inline void back_up(void) {
// 	end_ndx = dec_ndx(end_ndx);
// 	usart_send_blocking(USART2, '\010');
// 	usart_send_blocking(USART2, ' ');
// 	usart_send_blocking(USART2, '\010');
// }
// 
// /*
//  * A buffered line editing function.
//  */
// void get_buffered_line(void) {
// 	char	c;
// 	
// 	if (start_ndx != end_ndx) {
// 		return;
// 	}
// 	while (1) {
// 		c = usart_recv_blocking(USART2);
// 		if (c == '\r') {
// 			buf[end_ndx] = '\n';
// 			end_ndx = inc_ndx(end_ndx);
// 			buf[end_ndx] = '\0';
// 			usart_send_blocking(USART2, '\r');
// 			usart_send_blocking(USART2, '\n');
// 			return;
// 		}
// 		/* ^H or DEL erase a character */
// 		if ((c == '\010') || (c == '\177')) {
// 			if (buf_len == 0) {
// 				usart_send_blocking(USART2, '\a');
// 			} else {
// 				back_up();
// 			}
// 			/* ^W erases a word */
// 		} else if (c == 0x17) {
// 			while ((buf_len > 0) &&
// 				(!(isspace((int) buf[end_ndx])))) {
// 				back_up();
// 				}
// 				/* ^U erases the line */
// 		} else if (c == 0x15) {
// 			while (buf_len > 0) {
// 				back_up();
// 			}
// 			/* Non-editing character so insert it */
// 		} else {
// 			if (buf_len == (BUFLEN - 1)) {
// 				usart_send_blocking(USART2, '\a');
// 			} else {
// 				buf[end_ndx] = c;
// 				end_ndx = inc_ndx(end_ndx);
// 				usart_send_blocking(USART2, c);
// 			}
// 		}
// 	}
// }
// 
// 
// /*
//  * Called by libc stdio fwrite functions
//  */
// int _write(int fd, char *ptr, int len)
// {
// 	int i = 0;
// 	
// 	/*
// 	 * Write "len" of char from "ptr" to file id "fd"
// 	 * Return number of char written.
// 	 *
// 	 * Only work for STDOUT, STDIN, and STDERR
// 	 */
// 	if (fd > 2) {
// 		return -1;
// 	}
// 	while (*ptr && (i < len)) {
// 		usart_send_blocking(USART2, *ptr);
// 		if (*ptr == '\n') {
// 			usart_send_blocking(USART2, '\r');
// 		}
// 		i++;
// 		ptr++;
// 	}
// 	return i;
// }
// 
// /*
//  * Called by the libc stdio fread fucntions
//  *
//  * Implements a buffered read with line editing.
//  */
// int _read(int fd, char *ptr, int len)
// {
// 	int	my_len;
// 	
// 	if (fd > 2) {
// 		return -1;
// 	}
// 	
// 	get_buffered_line();
// 	my_len = 0;
// 	while ((buf_len > 0) && (len > 0)) {
// 		*ptr++ = buf[start_ndx];
// 		start_ndx = inc_ndx(start_ndx);
// 		my_len++;
// 		len--;
// 	}
// 	return my_len; /* return the length we got */
// }
