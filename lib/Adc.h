//
// Created by MKozuch on 2016-02-26.
//

#include <stdint.h>

#ifndef AVR_CLION_ADC_H
#define AVR_CLION_ADC_H

typedef enum adcchannel {ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7, ADC8, ADCBANDGAP=0x0E, ADCGND=0x0F } adcChannel;
typedef enum adcref {AREF, AVCC, BANDGAP=3} adcRef;
typedef enum adcresolution {EIGHTBIT, TENBIT} adcResolution;
typedef enum adctrigger {FREERUN, ACOMP, INT, T0CMA, T0OVF, T1CMB, T1OVF, T1CE, NOTRIGGER} adcTrigger;

/* initializes ADC with given set of parameters
 * autotriggering and ADC interrupt disabled by default
 * must be called before any other ADC operations take place */
uint16_t adc_setup(adcChannel, adcRef, adcResolution );

/* waits until current convresion is finished and changes ADC input */
int8_t adc_changeChannel(adcChannel); //TODO

/* enables interrupt at ADC ConversionComplete
 * this function must be called AFTER adc_setup */
int8_t adc_setupInterrupt(); // TODO

/* enables ADC autotriggering
 * this function must be called AFTER adc_setup */
int8_t adc_setTrigger(adcTrigger); //TODO

/* returns value from adc result register */
uint8_t adc_getResult_8();

/* initialzes conversion and returns high byte
 * note that it returns rubbish if ADC Left Adjust Result is not set */
uint8_t adc_read_8();

/* initialzes conversion and returns 10-bit result
 * note that it returns rubbish if ADC Left Adjust Result is set */
uint16_t adc_read_10();

/* change input channel, read sample and change channel back */
uint8_t adc_readFromChannel_8(adcChannel);

uint16_t adc_readTemp();
uint16_t adc_temperatureInit();
uint16_t _adc_temperatureToCelsius(uint16_t rawData);

#endif //AVR_CLION_ADC_H
