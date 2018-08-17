#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

const unsigned char str1[] = "Hello world\r\n";
const unsigned char str2[] = "1234567890 TEST 2\r\n";

static void setup(void)
{
    uart_init();
}

static void loop(void)
{
    while(1); //add blinking
}

int     main(void)
{
    setup();
    uart_transmit(str1);
    uart_transmit(str2);
    loop();

    return 0;
}