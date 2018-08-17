#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "get_temp.h"

static void	putnbr(int n)
{
    if (n < 0) {
        uart_sendChar('-');
		putnbr(n * -1);
	} else {
		if (n > 9) {
			putnbr(n / 10);
			putnbr(n % 10);
		} else {
            uart_sendChar(n + '0');
        }
	}
}


static void setup(void)
{
    uart_init();
    setup_adc();
}

static void loop(void)
{
    int c_temp = 0;
    int i = 0;
    const unsigned char str[] = " degrees Celsius\r\n";
    
    while(1) {
        putnbr(get_temp(c_temp));
        for (i = 0; str[i]; i++)
            uart_sendChar(str[i]);
    }
}

int     main(void)
{
    setup();
    loop();

    return 0;
}