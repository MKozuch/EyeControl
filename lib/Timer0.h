//
// Created by MKozuch on 2016-02-15.
//

#include <stdint.h>

#ifndef AVR_CLION_TIMER0_H
#define AVR_CLION_TIMER0_H

/* sets up Timer0 to generate interrupt at set interval
 * works with default clock 16MHz
 * dtus is time interval in microseconds
 * minimum is 4 and max is 1020
 * resolution is 4us */
uint8_t timer0_setupInterrrupt(uint16_t dtus);

// sets up Timer0 to work as PWM generator
uint8_t timer0_setupPwm(uint8_t dutycycle);
uint8_t timer0_setDuty(uint8_t dutycycle);

#endif //AVR_CLION_TIMER0_H
