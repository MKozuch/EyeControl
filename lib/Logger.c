//
// Created by MKozuch on 2016-02-28.
//

#include "Logger.h"
#include "Uart.h"
#include "StringConversions.h"

static char buffer[255] = {0};

void logger_logMessage(char* message)
{
    uart_transmitStringCrLf(message);
}

void logger_logVariable(char* message, int32_t value)
{
    strConv_intToDecStr(value, buffer);
    uart_transmitString(message);
    uart_transmitStringCrLf(buffer);
}

void logger_logRegister(char* message, int8_t value)
{
    strConv_charToHexStr(value, buffer);
    uart_transmitString(message);
    uart_transmitStringCrLf(buffer);
}