#ifndef PULL_UP_H
#define PULL_UP_H

#include <avr/io.h>
#include <util/delay.h>

#define LED DDB5
#define DDR_LED DDRB
#define PORT_LED PORTB

#define BUTTON DDD2
#define DDR_BUTTON DDRD
#define PORT_BUTTON PORTD
#define PIN_BUTTON PIND

#define LOW 0
#define HIGH 1

#define BIT_VAL(bit) (1 << (bit))
#define CLEAR_BIT(register, bit) ((register) &= ~(BIT_VAL(bit)))
#define SET_BIT(register, bit) ((register) |= (BIT_VAL(bit)))
#define DIGIT_WRITE_HIGH(register, bit) (SET_BIT((register), (bit)))
#define DIGIT_WRITE_LOW(register, bit) (CLEAR_BIT((register), (bit)))
#define DIGIT_PIN_OUTPUT(register, bit) (SET_BIT((register), (bit)))
#define DIGIT_PIN_INPUT(register, bit) (CLEAR_BIT((register), (bit)))
#define DIGIT_READ(register, bit) ((register) & (BIT_VAL(bit)))
#define TURN_ON_THE_PULL_UP(register, bit) (SET_BIT((register), (bit)))

#endif