//
// Created by MKozuch on 2016-02-15.
//

#include "Timer0.h"
#include <avr/io.h>

uint8_t timer0_setupInterrrupt(uint16_t dtus)
{
    // disconnect OC0A and OC0B and set CTC mode
    TCCR0A = 0x00;
    TCCR0A |= (1<<WGM01);
    TCCR0B &= ~(1<<WGM02);

    //set prescaller to 64
    TCCR0B = (TCCR0B & 0xF0) | 0x03;
    // prescalled f is 250kHz

    //dtmin = 4e-6s = 4us, dtmax = 1.02ms
    uint8_t cycles = dtus / 4;
    OCR0A = cycles;

    // enable interrupt
    TIMSK0 = 0 | (1<<OCIE0A);

    return 0;
}

// Setup timer 0 in fast PWM mode at pin PD6
uint8_t timer0_setupPwm(uint8_t duty)
{
    // set PD6 as output
    DDRD |= (1<<PD6);

    // set timer to operate in fast PWM mode (mode 7) at pin OC0A
    TCCR0A = (1<<COM0A1) | (0<<COM0A0) |(0<<COM0B1)| (0<<COM0B0) | (1<<WGM00) | (1<<WGM01);

    // set prescaler
    TCCR0B = (0<<WGM02) | (0<<CS02) | (0<<CS01) | (1<<CS00);

    // set duty cycle
    OCR0A = duty;

    return 0;
}

uint8_t timer0_setDuty(uint8_t dutycycle)
{
    OCR0A = dutycycle;
    return 0;
}
