//
// Created by MKozuch on 2016-02-17.
//

#include "StringConversions.h"


uint8_t strConv_charToHexStr(int8_t character, char buffer[])
{
    *buffer = '0';
    *(buffer + 1) = 'x';

    int8_t oldNibble = (character >> 4) & 0x0F;
    buffer[2] = (oldNibble >= 10) ? 65+oldNibble-10 : 48+oldNibble;

    int8_t youngNibble = character & 0x0F;
    buffer[3] = (youngNibble >= 10) ? 65+youngNibble-10 : 48+youngNibble;

    buffer[4] = 0;
    return 0;
}

uint8_t strConv_intToHexStr(int16_t integer, char buffer[])
{
    uint8_t oldestNibble;
    uint8_t byteCnt;

    *buffer = '0';
    *(buffer + 1) = 'x';

    for(byteCnt = 0; byteCnt<4; byteCnt++) {
        oldestNibble = (integer & 0xF000) >> 12;
        buffer[byteCnt+2] = (oldestNibble >= 10) ? 65 + oldestNibble - 10 : 48 + oldestNibble;
        integer <<= 4;
    }
    buffer[byteCnt+2] = 0;
    return 0;
}

uint8_t strConv_longToHexStr(int32_t integer, char buffer[])
{
    uint8_t i;
    uint8_t oldestNibble;

    *buffer = '0';
    *(buffer + 1) = 'x';

    for(i=2; i<10; ++i) {
        oldestNibble = (integer & 0xF0000000) >> 28;
        if (oldestNibble<10) buffer[i] = 48 + oldestNibble;
        else if (oldestNibble>=10 && oldestNibble<16) buffer[i] = 65 + (oldestNibble-10);
        integer <<= 4;
    }
    buffer[i+1] = 0;

    return 0;
}


uint8_t strConv_intToDecStr(int32_t integer, char buffer[])
{
    uint8_t isNegative; // this is a variable used to iterate through buffer while writing characters into it

    if (integer < 0) {
        buffer[0] = '-';
        integer = (~integer) + 1;
        isNegative = 1;
    }
    else if (integer>0) isNegative = 0;
    else
    {
        buffer[0] = '0';
        buffer[1] = 0;
        return 0;
    }

    // max decimal length of long is 10
    uint8_t remainders[10] = {0}; // this array holds individual digits of integer in reverse order
    uint8_t remainder;
    uint8_t i;

    for (i = 0; integer != 0; i++) // in each iteration divide integer by 10 and store remainder
    {
        remainder = integer % 10;
        remainders[i] = remainder;
        integer = (integer-remainder) / 10;
    }

    uint8_t integerLen = i; // number of digits in integer

    for (i = 0; i<integerLen; i++) // in each iteration take a digit from remainders and put into buffer in reverse
    {
        buffer[i+isNegative] = remainders[integerLen-i-1] + 48;
    }

    buffer[i+isNegative] = 0;
    return 0;
}