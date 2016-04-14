//
// Created by MKozuch on 2016-03-09.
//

#include "Timer1.h"
#include "avr/io.h"

int8_t timer1_setupOutputCompareB10ms()
{
    TCCR1A = 0; // disconnect Output Compare pins

    TCCR1B &= ~(1<<WGM13);
    TCCR1B |= (1<<WGM12); // set CTC mode (mode 8)

    TCCR1B = (TCCR1B & 0xF8) | (0x03); // set prescaller 64

    TIMSK1 = 0; // disable all interrupts at Timer1

    OCR1A = 0x09C4; // set TOP value for Timer1
    OCR1B = 0x09C4; // set value for output Compare Match B

    return 0;
}
