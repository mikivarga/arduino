#ifndef LED_BLINKING_H
#define LED_BLINKING_H

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN DDB5
#define DDR_LED DDRB
#define PORT_LED PORTB

#define BIT_VAL(bit) (1 << (bit)) // existing macro in avr
#define CLEAR_BIT(register, bit) ((register) &= ~(BIT_VAL(bit)))
#define SET_BIT(register, bit) ((register) |= (BIT_VAL(bit)))

#define DIGIT_WRITE_HIGH(register, bit) (SET_BIT((register), (bit)))
#define DIGIT_WRITE_LOW(register, bit) (CLEAR_BIT((register), (bit)))
#define DIGIT_PIN_OUTPUT(register, bit) (SET_BIT((register), (bit)))

#endif