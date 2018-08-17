#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "interrupt_button.h"

#define NO_FORCE 0b0000000
#define NORMAL 0b00000000
#define HIGH_BYTE 0xf4
#define LOW_BYTE 0x23

static void setup(void)
{
  DIGIT_PIN_OUTPUT(DDR_LED, LED);
  cli();
  TCCR0A = 0;
  TCCR0B = 0;
  TIMSK0 = (1<<TOIE0);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  sei();
}

static void loop(void)
{
  for (;;) {}
}

int main(void)
{
  setup();
  loop();

  return 0;
}

int flag = 0;

ISR(TIMER0_OVF_vect)
{
  flag++;
  TCNT0 += 6;
  if (flag == 1000) { 
    PORT_LED ^= BIT_VAL(LED);
    flag = 0;
  }
}
