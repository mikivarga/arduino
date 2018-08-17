#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "interrupt_button.h"

#define PRESCALER 0b00000100
#define NO_FORCE 0b0000000
#define NORMAL 0b00000000
#define HIGH_BYTE 0xf4
#define LOW_BYTE 0x23

static void setup(void)
{
  DIGIT_PIN_OUTPUT(DDR_LED, LED);
  cli();
  TCCR1A = NORMAL;
  TCCR1B = PRESCALER;
  TCCR1C = NO_FORCE;
  OCR1AH = HIGH_BYTE;
  OCR1AL = LOW_BYTE;
  OUTUT_COMPARE(TIMSK1, OCIE1A);
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

ISR(TIMER1_COMPA_vect)
{
 PORT_LED ^= BIT_VAL(LED);
}
