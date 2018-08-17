#ifndef UART_H
#define UART_H

#include <stdlib.h>
#include "ring_buf.h"

void uart_init(void);
void uart_sendChar(unsigned char c);
unsigned char usart_receiveChar(void);
void uart_transmit(const unsigned char *data);

#endif