//
// Created by MKozuch on 2016-02-26.
//

#include "Delay.h"

void Delay_s(int iSeconds){
    for(int i = 0; i<iSeconds; ++i){
        Delay_ms(1000);
    }
}

void Delay_ms(int iMilliseconds){
    for(int i = 0; i<iMilliseconds; ++i){
        Delay_us(1000);
    }
}

void Delay_us(int iMicroseconds){
    volatile unsigned long clocks = iMicroseconds * (F_CPU/1000000);
    volatile unsigned long cycles = clocks/35;
    while (--cycles){}
}
