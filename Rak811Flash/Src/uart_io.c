/*
 * uart_io.c
 *
 *  Created on: Aug 13, 2018
 *      Author: uli
 */


#include "stm32l1xx_hal.h"

int __io_putchar(int ch) {
	while ((USART1->SR & UART_FLAG_TC) == (uint16_t)RESET) {}
	USART1->DR = (char) ch & (uint16_t) 0x01ff;
	return 0;
}
int __io_getchar(void) {
	while ((USART1->SR & UART_FLAG_RXNE) == (uint16_t)RESET) {}
	char c = (char)(USART1->DR & (uint16_t)0x01FF);
	return (int)c;
}
