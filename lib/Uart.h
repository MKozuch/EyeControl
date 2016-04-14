//
// Created by MKozuch on 2016-02-15.
//

#ifndef AVR_CLION_UART_H
#define AVR_CLION_UART_H

uint8_t uart_setup(uint32_t baud);
uint8_t uart_putChar(char c);
char uart_getChar();
int8_t uart_transmitString(char *str);
int8_t uart_transmitStringCrLf(char *str);

int8_t uart_isInitialized;

#endif //AVR_CLION_UART_H
