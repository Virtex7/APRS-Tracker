#ifndef USART_H_
#define USART_H_
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <stdio.h>
#include <ctype.h>
int _read(int fd, char *ptr, int len);
int _write(int fd, char *ptr, int len);
void get_buffered_line(void);
void back_up(void);
void usart_setup(void);
void usart_clock_setup(void);
#endif //--USART_H_