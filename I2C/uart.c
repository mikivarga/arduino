#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define FOSC 16000000
#define BAUD 9600
#define UBRR_VAL FOSC/16/BAUD-1

#include <util/setbaud.h>

t_ring_buf rb_tx;

void uart_init(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    rb_init(&rb_tx);
    sei();
}

void uart_sendChar(unsigned char c)
{
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = c;
}

unsigned char usart_receiveChar(void)
{
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
}

void uart_transmit(const unsigned char *data)
{
    rb_write(&rb_tx, data);
    UCSR0B |= _BV(UDRIE0);
}

ISR(USART_UDRE_vect)
{
    if (rb_save_elem(&rb_tx) > 0) {
        UDR0 = rb_read_byte(&rb_tx);
    }
    else {
      UCSR0B &= ~_BV(UDRIE0);
    }
}