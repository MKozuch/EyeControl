//
// Created by MKozuch on 2016-02-15.
//

#define F_CPU 16000000UL
#include <avr/interrupt.h>

#include <avr/io.h>
#include "lib/Uart.h"
#include "lib/Led.h"
#include "lib/StringConversions.h"
#include "lib/Button.h"
#include "lib/Delay.h"
#include "lib/Adc.h"
#include "lib/Logger.h"
#include "lib/Timer0.h"
#include "lib/Timer1.h"
#include "lib/Timer2.h"

#include "eyeControl/eyeControl.h"
#include "eyeControl/eyeControl_buffer.h"
#include "lib/Eeprom.h"

#define _DEBUG

int main(void)
{
    uart_setup(9600);

    led_setup();

    led_heartbeatInit();

    timer2_servoSetup();

    eyeControl_setup();
    eyeControl_init();

    for(uint8_t i = 0; i < 3; i++)
    {
        led_on(ALLLED);
        Delay_ms(200);
        led_off(ALLLED);
        Delay_ms(200);
    }

    sei();

    /*uint8_t ByteOfData;
    uint8_t ByteAddress = 46;
    ByteOfData = Eeprom_readByte(ByteAddress);
    ++ByteOfData;
    Eeprom_writeByte(ByteAddress, ByteOfData);
    logger_logVariable("eeprom @46: ", ByteOfData);*/

    int8_t ser = timer2_SERVO_NEUTRAL_PULSE;
    timer2_servoGotoNeutral();

    int16_t ticks = 0;
    Delay_ms(1);

    while(1)
    {
        logger_logVariable("", mean);

        led_off(ALLLED);

        // diode control
        if(ECSignal == LEFT) led_on(LEFTLED);
        else if(ECSignal == RIGHT) led_on(RIGHTLED);
        else if (ECSignal == REST) led_on(RESTLED);
        else if (ECSignal == CLIPPING) led_on(BLINKLED);

        // servo control
        if(ECSignal == LEFT && ticks%30 == 0) ser-=1;
        else if(ECSignal == RIGHT && ticks%30 == 0) ser+=1;
        else if (ECSignal == REST);
        else if (ECSignal == CLIPPING)
        {
            ser = timer2_SERVO_NEUTRAL_PULSE;
            timer2_servoGotoNeutral();
        }
        if(ser < timer2_SERVO_MIN_PULSE) ser = timer2_SERVO_MIN_PULSE;
        else if (ser > timer2_SERVO_MAX_PULSE) ser = timer2_SERVO_MAX_PULSE;
        timer2_servoSetPulseWidth(ser);

        Delay_ms(10);
        ticks += 1;
        ticks %= 1000;

    }
}



/*uint32_t timeCtr = 0;
uint8_t adcBuffer[2] = {0};
uint8_t k = 0;
uint16_t sample= 0;
uint16_t prevSample = 0;
uint8_t newSample = 0;
ISR(TIMER0_COMPA_vect)
{
    if (timeCtr >= 10)
    {
        prevSample = sample;
        sample = adc_getSample8();

        newSample = (sample+prevSample) >> 1;
        logger_logVariable("", newSample);
    }
    else timeCtr += 1;
}*/

/*
ISR(INT1_vect)
{
    ;
}*/
