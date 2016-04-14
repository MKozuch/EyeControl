//
// Created by MKozuch on 2016-02-17.
//

#ifndef AVR_CLION_STRINGCONVERSIONS_H
#define AVR_CLION_STRINGCONVERSIONS_H

#include <stdint.h>

uint8_t strConv_charToHexStr(int8_t, char[]);
uint8_t strConv_intToHexStr(int16_t, char[]);
uint8_t strConv_longToHexStr(int32_t, char[]);
uint8_t strConv_intToDecStr(int32_t, char[]);

#endif //AVR_CLION_STRINGCONVERSIONS_H
