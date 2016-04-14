//
// Created by MKozuch on 2016-03-07.
//

#ifndef AVR_CLION_EYECONTROL_H
#define AVR_CLION_EYECONTROL_H

#include <stdint.h>

#define JOYXPIN ADC0
#define JOYYPIN ADC1
#define SIGNALPIN ADC2
//#define SIGNALPIN JOYXPIN
#define REFERENCEPIN ADC3
#define SIGNALFPIN ADC4

typedef enum states {INIT, LOOP} eyeControl_states;
typedef enum signals {REST, LEFT, RIGHT, CLIPPING} eyeControl_signals;
volatile eyeControl_signals ECSignal;

int8_t eyeControl_setup();
int8_t eyeControl_init();
eyeControl_signals eyeControl_getSignal();

/* return standard deviation of noise */
int8_t _eyeControl_estimateNoise();

/* wait until signal base level is settled */
int8_t _eyeControl_waitForSettle();

/* get value of signal baseline */
int8_t _eyeControl_getBaseline();

int16_t mean;

#endif //AVR_CLION_EYECONTROL_H
