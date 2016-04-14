//
// Created by mik on 2016-03-30.
//

#include <stdint.h>

#ifndef AVR_CLION_TIMER2_H
#define AVR_CLION_TIMER2_H

uint8_t timer2_servoSetup();
uint8_t timer2_servoSetPulseWidth(uint8_t);
uint8_t timer2_servoGotoNeutral();

uint8_t timer2_servoSetAngle(int8_t);

uint8_t timer2_SERVO_MIN_PULSE;
uint8_t timer2_SERVO_MAX_PULSE;
uint8_t timer2_SERVO_NEUTRAL_PULSE;



#endif //AVR_CLION_TIMER2_H
