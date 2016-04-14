//
// Created by mik on 2016-03-30.
//

#include "Timer2.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define SERVOPIN PB3

// 1 tick is 0,1 ms
// that is 15 ticks for neutral, 10 for minimum and 20 for maximum

#define SERVOMINPULSE 6
#define SERVOMAXPULSE 23
#define SERVONEUTRAL 15
#define SERVOPERIOD 500

uint8_t timer2_SERVO_MIN_PULSE = SERVOMINPULSE;
uint8_t timer2_SERVO_MAX_PULSE = SERVOMAXPULSE;
uint8_t timer2_SERVO_NEUTRAL_PULSE = SERVONEUTRAL;

uint16_t servoTicks = 0; // number of ticks since rising edge
//uint16_t servoPeriod = 200; // number of ticks required for full 20ms period
uint16_t servoPulseWidth = 15;

uint8_t timer2_servoSetup()
{
    TCCR2A = 0;

    // set timer if CTC mode
    TCCR2A |= (1<<WGM21);
    TCCR0B &= ~(1<<WGM22);

    // set timer prescaler at 64 giving frequency of 250kHz, dt=4ums
    TCCR2B = (TCCR2B & 0xF8) | 0x04;

    // set top 25 giving resolution of 0,1ms
    OCR2A = 25;

    // enable timer compare interrupt
    TIMSK2 |= (1<<OCIE2A);

    // set OC2A as output
    DDRB |= (1<<SERVOPIN);

    servoPulseWidth = SERVONEUTRAL;
    servoTicks = 0;

    return 0;
}


uint8_t timer2_servoSetPulseWidth(uint8_t pulsewidth)
{
    if (pulsewidth < SERVOMINPULSE) pulsewidth = SERVOMINPULSE;
    else if (pulsewidth > SERVOMAXPULSE) pulsewidth = SERVOMAXPULSE;
    else servoPulseWidth = pulsewidth;
    return 0;
}

uint8_t timer2_servoGotoNeutral()
{
    timer2_servoSetPulseWidth(SERVONEUTRAL);
    return 0;
}

ISR(TIMER2_COMPA_vect)
{
    if (servoTicks == 0)
    {
        PORTB |= (1<<SERVOPIN);
        servoTicks += 1;
    }
    else if (servoTicks == servoPulseWidth)
    {
        PORTB &= ~(1<<SERVOPIN);
        servoTicks += 1;
    }
    else if (servoTicks == SERVOPERIOD)
    {
        servoTicks = 0;
    }
    else
    {
        servoTicks += 1;
    }
}