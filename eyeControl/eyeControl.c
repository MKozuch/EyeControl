//
// Created by MKozuch on 2016-03-07.
//

#include "eyeControl.h"

#include "../lib/Uart.h"
#include "../lib/Adc.h"
#include "../lib/Timer1.h"
#include "../lib/Logger.h"
#include "../lib/Led.h"
#include "../lib/Delay.h"
#include "eyeControl_buffer.h"
#include <avr/interrupt.h>

#define THRESHOLD 25
#define TIMEOUT 300

int8_t referenceValue = 0;
uint16_t ticks = 0;

int8_t eyeControl_setup()
{
    adc_setup(SIGNALPIN, AVCC, EIGHTBIT);
    adc_setTrigger(T1CMB);
    adc_setupInterrupt();
    timer1_setupOutputCompareB10ms();
    return 0;
}

int8_t eyeControl_init()
{
    // estimate reference level
    uint16_t sum = 0;
    for(uint8_t i = 0; i< 8; ++i)
    {
        sum += adc_readFromChannel_8(REFERENCEPIN);
        Delay_ms(10);
    }
    referenceValue = (sum>>3);
    logger_logVariable("Reference value: ", referenceValue);

    ticks = 0;
    ECSignal = REST;
    return 0;
}

int8_t _eyeControl_estimateNoise()
{
    return 0;
}

ISR(ADC_vect)
{
    led_hearbeat();

    uint8_t adcValue = adc_getResult_8();
    //uint8_t referenceValue = adc_readFromChannel_8(REFERENCEPIN); // can be changed for const for optimisation

    int8_t sample = adcValue - referenceValue;
    buffer_addToBuffer(sample);

    //static int16_t mean = 0; // uncomment when mean loses global scope
    mean = 0;
    for(uint8_t i = 0; i<BUFFERSIZE; i+=1)
    {
        mean +=  eyeControl_buffer[i];
    }
    mean >>= BUFFERLOGSIZE;

    // different way of calculating moving average
    /*mean += (sample / BUFFERSIZE);
    mean -= (*(buffer_oldestElement()) / BUFFERSIZE);*/

    int8_t thresholdHi = THRESHOLD;
    int8_t thresholdLo = -THRESHOLD;

    // remember to keep track on time since last threshold transition in order to timeout
    eyeControl_signals currentSignal = ECSignal;
    static eyeControl_signals prevState;
    eyeControl_signals nowState;

    if(adcValue==0 || adcValue == 255) nowState = CLIPPING;
    else if(mean > thresholdHi) nowState = LEFT;
    else if(mean < thresholdLo) nowState = RIGHT;
    else nowState = REST;

    // clipping detection
    if(nowState == CLIPPING) ECSignal = CLIPPING;
    if(prevState == CLIPPING && nowState != CLIPPING) ECSignal = nowState;

    // transition from zero to high
    else if(prevState == REST && nowState == LEFT)
    {
        if (currentSignal == REST) ECSignal = LEFT;
        if (currentSignal == LEFT) ECSignal = LEFT;
        if (currentSignal == RIGHT) ECSignal = REST;
    }

    // transition from zero to low
    else if(prevState == REST && nowState == RIGHT)
    {
        if (currentSignal == REST) ECSignal = RIGHT;
        if (currentSignal == RIGHT) ECSignal = RIGHT;
        if (currentSignal == LEFT) ECSignal = REST;
    }

    // transition from high to zero
    else if(prevState == LEFT && nowState == REST);

    // transition from low to zero
    else if(prevState == RIGHT && nowState == REST);

    prevState = nowState;

    /*if(nowState == CLIPPING) ECSignal = CLIPPING;
    if(currentSignal == REST && nowState == LEFT) ECSignal = LEFT;
    if(currentSignal == REST && nowState == RIGHT) ECSignal = RIGHT;
    if (ticks > timeout) ECSignal = REST;
    if(currentSignal == LEFT && nowState == RIGHT) ECSignal = REST;
    if(currentSignal == RIGHT && nowState == LEFT) ECSignal = REST;
    if(currentSignal == CLIPPING) ECSignal = REST;

    if(nowState == CLIPPING) ECSignal = CLIPPING;

    if (ECSignal ~= currentSignal) ticks = 0;*/

    if(currentSignal != ECSignal) ticks = 0;
    else if(ticks == TIMEOUT)
    {
        if(ECSignal == LEFT || ECSignal == RIGHT) ECSignal = REST;
        ticks = 0;
    }
    else ticks += 1;

    TIFR1 |= (1<<OCF1B); // clear timer1 compare match flag B
    ADCSRA |= (1<<ADIF); // clear ADC interrupt flag to prevent from firing next interrupt
    led_hearbeat();
}