//
// Created by MKozuch on 2016-02-15.
//

#include <avr/io.h>
#include "Uart.h"

int8_t uart_isInitialized = 0;

uint8_t uart_setup(uint32_t baud)
{
    // set asynchronous operation
    UCSR0C &= !((1<<UMSEL00) | (1<<UMSEL01));

    // set baud rate
    uint32_t ubrr = (F_CPU/(16*baud)) -1;
    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)(ubrr);

    // enable Rx and Tx
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);

    // default frame: no parity, 1 stop, 8 data
    UCSR0C &= !((1<<UPM00) | (1<<UPM01));
    UCSR0C &= !(1<<USBS0);
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);

    return 0;
}

uint8_t uart_setupInterrupt(uint32_t baud, uint8_t txInterEnable, uint8_t rxInterEnable)
{
    uart_setup(baud);

    // enable RX Complete Interrupt
    if(rxInterEnable) UCSR0B |= (1 << RXCIE0);

    // enable TX Complete Interrupt
    if(txInterEnable) UCSR0B |= (1<<TXCIE0);

    uart_isInitialized = 1;

    return 0;
}

uint8_t uart_putChar(char c)
{
    // wait until buffer is empty
    while(!(UCSR0A & (1<<UDRE0))) {;}

    // put character into buffer
    UDR0 = c;

    return 0;
}

char uart_getChar()
{
    // wait for data
    while(!(UCSR0A & (1<<RXC0))) {;}

    // pull data out from buffer
    char c = UDR0;

    return c;
}


// transmit string via uart and return number of chars sent
int8_t uart_transmitString(char *str)
{
    char *c = str;
    while (*c)
    {
        uart_putChar(*c);
        c++;
    }
    return(c-str);
}

// transmit string with CRLF sequence at the end
int8_t uart_transmitStringCrLf(char *str)
{
    int8_t retCode = uart_transmitString(str);
    retCode += uart_transmitString("\r\n");
    return retCode;
}