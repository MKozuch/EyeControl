//
// Created by mik on 2016-03-29.
//

#ifndef AVR_CLION_EEPROM_H
#define AVR_CLION_EEPROM_H

#include <stdint.h>

uint8_t Eeprom_init();
uint8_t Eeprom_writeByte(uint8_t address, uint8_t value);
uint8_t Eeprom_readByte(uint8_t address);

#endif //AVR_CLION_EEPROM_H
