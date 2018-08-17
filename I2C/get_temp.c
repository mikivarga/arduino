#include "get_temp.h"


void start_and_wait_conversion(void)
{
    ADCSRA |= _BV(ADSC);
    while ((ADCSRA & (1<<ADSC)) != 0)
    ;
}

void setup_adc(void)
{
    /* Setup ADC to use int 1.1V reference 
    and select temp sensor channel */
    ADMUX = (1<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (1<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
     /* Set conversion time to 
    112usec = [(1/(8Mhz / 64)) * (14 ADC clocks  per conversion)]
     and enable the ADC*/
    ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADEN);
    start_and_wait_conversion();
}

int get_temp(int c_temp)
{
    start_and_wait_conversion();

    //Get rid of float point. Pay attention that ADC is 8 bit register
    c_temp = (ADC - 324.31)/1.22;

    return c_temp;
}