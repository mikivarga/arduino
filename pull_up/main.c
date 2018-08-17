#include <stdbool.h>
#include "pull_up.h"

static void setup(void)
{
  DIGIT_PIN_OUTPUT(DDR_LED, LED);
  DIGIT_PIN_INPUT(DDR_BUTTON, BUTTON);
  TURN_ON_THE_PULL_UP(PORT_BUTTON, BUTTON);
}

static void loop(void)
{
  bool buttonState = LOW;

  for(;;) {
    buttonState = DIGIT_READ(PIN_BUTTON, BUTTON);
    if (buttonState == HIGH) {
       DIGIT_WRITE_HIGH(PORT_LED, LED);
    }
    else {
      DIGIT_WRITE_LOW(PORT_LED, LED);      
    }
  }
}

int main(void)
{
  setup();
  loop();
  return (0);
}
