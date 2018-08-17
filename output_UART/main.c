#include <avr/io.h>

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

static void USART_Transmit(unsigned char data )
{
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    UDR0 = data;
}

#if 0
ISR: Transmit done
1. Load next char from buffer
2. 
    1) loop buffer

      v
    [ . . . . . . . . . . . . . . . . . . . . . ]
                                  v
    [ H e l l o _ w o r l d ! \n\0. . . . . . . ]
      ^
        ^                                     v
    [ H e l l o _ w o r l d ! \n\0T E S T 1 \n\0]
                ^
              v
    [ T e s \n\0_ w o r l d ! \n\0T E S T 1 \n\0]
                ^
#endif

static unsigned char USART_Receive( void )
{
    while ( !(UCSR0A & (1<<RXC0)) )
    ;
    return UDR0;
}

static void setup(void)
{
    init_uart();
}

static void printf_str(const char *str)
{
    while (*str)
        USART_Transmit(*str++);
}

int main(void)
{
    char data;
    const char s[] = "Hello";
    char *data_rec = "Receive character: ";
    char *data_tran = "Transmit character: ";
    
    setup();
    printf_str(s);
    while(1) {
        USART_Transmit('\n');
        USART_Transmit('\r');
        printf_str(data_rec);
        data =  USART_Receive();
        USART_Transmit(data);
        USART_Transmit('\n');
        USART_Transmit('\r');
        printf_str(data_tran);
        USART_Transmit(data);
    }

    return 0;
}