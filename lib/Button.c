//
// Created by MKozuch on 2016-02-25.
//

#include "Button.h"
#include <avr/io.h>

/* Translate button name to its bit mask identifier */
int8_t _translate_btn_name(ButtonName btn)
{
    switch(btn){
        case 0:
            return PD2;
        case 1:
            return PD3;
        case 2:
            return PD4;
        case 3:
            return PD5;
        case 4:
            return PD6;
        default:
            return -1;
    }
}


int8_t button_setup(ButtonName btn)
{
    int8_t physicalPin = _translate_btn_name(btn);
    DDRD &= ~(1<<physicalPin);
    PORTD |= (1<<physicalPin); // enable internal pullup
    return 0;
}


int8_t button_getState(ButtonName btn)
{
    int8_t physicalPin = _translate_btn_name(btn);
    return (PIND & (1<<physicalPin) ? 1: 0);
}


int8_t button_setupInterrupt(ButtonName btn)
{
    if (btn == BTNSEL) {
        // INT0 is PD2
        // enable INT0 on falling edge
        EICRA &= ~(1 << ISC00);
        EICRA |= (1 << ISC01);

        // enable external interrupt on INT0
        EIMSK |= (1 << INT0);
    }
    else if (btn == BTN3){
        // INT1 is PD3
        // enable INT1 on falling edge
        EICRA &= ~(1 << ISC10);
        EICRA |= (1 << ISC11);

        // enable external interrupt on INT0
        EIMSK |= (1 << INT1);
    }
    return 0;
}
