//
// Created by MKozuch on 2016-02-26.
//

// #define _DEBUG
#include "Adc.h"
#include <avr/io.h>

#ifdef _DEBUG
#include "Logger.h"
#endif

uint16_t adc_setup(adcChannel channel, adcRef reference, adcResolution resolution)
{
    // set reference for ADC
    ADMUX = (ADMUX & (0xFF>>2)) | (reference << 6);

    // set ADC input
    ADMUX = (ADMUX & 0xF0) | (0x0F & channel);

    // set 8 or 10-bit resolution
    if (resolution == EIGHTBIT) ADMUX |= (1<<ADLAR);
    else if (resolution == TENBIT) ADMUX &= ~(1<<ADLAR);

    // set 128 prescaler for ADC clock
    ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));

    // disable autotrigger
    ADCSRA &= ~(1<<ADATE);

    // enable ADC
    ADCSRA |= (1<<ADEN);

    // read first sample
    adc_read_8();

#ifdef _DEBUG
    logger_logMessage("ADC setup...");
    logger_logRegister("\tADMUx: ", ADMUX);
    logger_logRegister("\tADCSRA: ", ADCSRA);
#endif

    return 0;
}

int8_t adc_setupInterrupt()
{
    ADCSRA |= (1<<ADIE);
#ifdef _DEBUG
    logger_logMessage("ADC setup interrupt...");
    logger_logRegister("\tADCSRA: ", ADCSRA);
#endif
    return 0;
}

int8_t adc_setTrigger(adcTrigger trigger)
{
    if (trigger > NOTRIGGER) return 1;
    else if (trigger == NOTRIGGER)
    {
        ADCSRA &= ~(1<<ADATE); // disable autotriggering
        return 0;
    }
    else {
        ADCSRB = (ADCSRB & 0xF8) | (trigger & 0x07);
        ADCSRA |= (1 << ADATE);
        return 0;
    }
}

int8_t adc_changeChannel(adcChannel channel)
{
    // the result of changing Analog Channel Selection Bits only goes in effect after current conversion
    while( ADCSRA & (1<<ADSC) );

    // set ADC input
    ADMUX = (ADMUX & 0xF0) | (0x0F & channel);

    return 0;
}

uint8_t adc_getResult_8()
{
    // return conversion result
    uint8_t sample = ADCH;
    return sample;
}

uint8_t adc_read_8()
{
    // start conversion
    ADCSRA |= (1<<ADSC);

    // wait for conversion completion
    while( ADCSRA & (1<<ADSC) );

    // return result
    uint8_t sample = ADCH;
    return sample;
}

uint16_t adc_read_10()
{
    // start conversion
    ADCSRA |= (1<<ADSC);

    // wait for conversion completion
    while( ADCSRA & (1<<ADSC) );

    // return result
    uint8_t sLo = ADCL;
    uint16_t sHi = ADCH<<8;
    uint16_t sample = sLo + sHi;
    return sample;
}

uint8_t adc_readFromChannel_8(adcChannel channel)
{
    // wait for previous conversion to finish
    while( ADCSRA & (1<<ADSC) );

    // remember contents of ADMUX
    uint8_t tempAdmux = ADMUX;

    // change ADC input
    ADMUX = (ADMUX & 0xF0) | (0x0F & channel);

    // start conversion
    ADCSRA |= (1<<ADSC);

    // wait for conversion completion
    while( ADCSRA & (1<<ADSC) );

    // return result
    uint8_t sample = ADCH;

    // restore original ADMUX value
    ADMUX = tempAdmux;

    return sample;
}


uint16_t adc_temperatureInit()
{
    // set internal bandgap reference as reference for ADC
    ADMUX |= ((1<<REFS1) | (1<<REFS0));

    // set ADC8 as ADC input
    ADMUX = (ADMUX & 0xF0) | (0x0F & 0x08);

    // set 128 prescaler for ADC clock
    ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));

    // disable autotrigger
    ADCSRA &= ~(1<<ADATE);

    // enable ADC
    ADCSRA |= (1<<ADEN);

    // read first sample
    adc_readTemp();

    return 0;
}

uint16_t adc_readTemp()
{
    // start conversion
    ADCSRA |= (1<<ADSC);

    // wait for conversion completion
    while( ADCSRA & (1<<ADSC) );

    //conversion result
    uint8_t tLo = ADCL;
    uint8_t tHi = ADCH;

    uint16_t rawTemp = (tHi<<8) + tLo;
    uint16_t temp = _adc_temperatureToCelsius(rawTemp);
    return temp;
}

uint16_t _adc_temperatureToCelsius(uint16_t rawData)
{
    float rawVoltage = ((float)rawData / 1024) * 1100;
    uint16_t temperature = rawVoltage-290;
    return temperature;

    /*
    float p0[] = {-45, 242};
    float p1[] = {25,  314};
    float p2[] = {85,  380};

    float a1 = (p0[1]-p1[1]) / (p0[0]-p1[0]);
    float b1 = p1[1] - a1 * p1[0];
    float a2 = (p1[1]-p2[1]) / (p1[0]-p2[0]);
    float b2 = p1[1] - a2 * p1[0];

    uint16_t temperature;

    if(rawVoltage > p1[1]) temperature = a2 * rawVoltage + b2;
    else if (rawVoltage < p1[1]) temperature = a1 * rawVoltage + b1;
    else temperature = p1[0];

    return temperature;
     */
}