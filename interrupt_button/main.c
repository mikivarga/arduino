#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "interrupt_button.h"

#include <util/delay.h>

volatile static bool buttonState = false;
volatile static bool ledState = true;
static const int MSEC = 125;

static void setup(void)
{
  DIGIT_PIN_OUTPUT(DDR_LED, LED);
  DIGIT_PIN_INPUT(DDR_BUTTON, BUTTON);
  TURN_ON_THE_PULL_UP(PORT_BUTTON, BUTTON);
  cli();
  TURN_ON_INT(EIMSK, INT0);
  SET_INT_TO_TRIGGER_ON_ANY_LOGIC_CHANGE(EICRA, ISC00);
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

static void turn_on_of_led(void)
{
  if ((ledState = !ledState)) {
    DIGIT_WRITE_HIGH(PORT_LED, LED);
  }
  else {
    DIGIT_WRITE_LOW(PORT_LED, LED);
  }
}

static bool check_button(void)
{
  if (DIGIT_READ(PIN_BUTTON, BUTTON) != buttonState) {
    _delay_ms(MSEC);
    if (DIGIT_READ(PIN_BUTTON, BUTTON) != buttonState &&\
    (buttonState = DIGIT_READ(PIN_BUTTON, BUTTON))) {
      return true;
    }
  }
  return false;
}

ISR(INT0_vect)
{
  if (check_button()) {
    turn_on_of_led();
  } 
}
