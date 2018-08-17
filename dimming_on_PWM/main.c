#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>

#define LED_PIN PB1
#define DDR_LED DDRB
#define PORT_LED PORTB
#define BOTTOM 0x00
#define TOP 0xff
#define ML_SEC 10

#define DIGIT_PIN_OUTPUT(reg, bit) (sbi(reg, bit))

static unsigned int brightness = 0;
static int fade = 1;
static int cnt_timer = 0;

static void init_pwm(void)
{
    TCCR1A |= _BV(COM1A1) | _BV(WGM10);
    TCCR1B |= _BV(CS10) | _BV(WGM12);
}

static void init_timer_0(void)
{
    TCCR0A = 0;
    TCCR0B = 0;
    TIMSK0 = (1 << TOIE0);
    TCCR0B |= (1 << CS01) | (1 << CS00);
    sei();
}

static void    setup(void)
{
    init_pwm();
    init_timer_0();
    DIGIT_PIN_OUTPUT(DDR_LED, LED_PIN);
}

static void    loop()
{
    while (1);
}

int     main(void)
{
    setup();
    loop();

    return 0;
}

static void set_pwm_output(int level)
{
    OCR1A = level;
}

static void analog_write(void)
{
    set_pwm_output(brightness);
    brightness += fade;
    
    if (brightness == BOTTOM || brightness == TOP) {
        fade = -fade;
    }
}

ISR(TIMER0_OVF_vect)
{
    if (cnt_timer++ == ML_SEC) {
        analog_write();
        cnt_timer = 0;
    }
}