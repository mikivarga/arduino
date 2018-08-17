#include "led_blinking.h"

static const int BLINK_DELAY_MS = 1000;

static void setup(void)
{
  DIGIT_PIN_OUTPUT(DDR_LED, LED_PIN);
}

static void loop(void)
{
  for(;;) { // while is not a bad practice; for is best practice in C++ world
    DIGIT_WRITE_HIGH(PORT_LED, LED_PIN);
    _delay_ms(BLINK_DELAY_MS);
    DIGIT_WRITE_LOW(PORT_LED, LED_PIN);
    _delay_ms(BLINK_DELAY_MS);
  }
}

int main(void)
{
  setup();
  loop();
  return (0); // Code style
}
