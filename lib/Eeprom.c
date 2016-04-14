//
// Created by mik on 2016-03-29.
//

#include "Eeprom.h"
#include <avr/io.h>

uint8_t Eeprom_init()
{
    return 0;
}

uint8_t Eeprom_writeByte(uint8_t address, uint8_t value)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));

    /* Set up address and Data Registers */
    EEAR = address;
    EEDR = value;

    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);

    return 0;
}

uint8_t Eeprom_readByte(uint8_t address)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));

    /* Set up address register */
    EEAR = address;

    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);

    /* Return data from Data Register */
    return EEDR;
}