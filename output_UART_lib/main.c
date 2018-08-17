#include <avr/io.h>
#include <compat/deprecated.h>
//#include <util/delay.h>
#include <stdio.h>

#define FOSC 16000000
#define BAUD 9600
#define UBRR_VAL FOSC/16/BAUD-1

#include <util/setbaud.h>

static void init_uart(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

static void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

static char uart_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

static void setup(void)
{
    FILE uart_output =\
        FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
    FILE uart_input =\
        FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
    stdout = &uart_output;
    stdin = &uart_input;
    init_uart();
}

void loop(unsigned char input)
{
    while (1) {
        input = getchar();
        printf("Receive %c\n", input);
        //_delay_ms(2000);
    }
}

int main(void)
{
    unsigned char input = 0;

    setup();
    puts("HELLO");
    loop(input);

    return 0;
}