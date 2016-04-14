//
// Created by MKozuch on 2016-02-28.
//

#include <stdint.h>

#ifndef AVR_CLION_LOGGER_H
#define AVR_CLION_LOGGER_H

void logger_logMessage(char*);
void logger_logVariable(char*, int32_t );
void logger_logRegister(char*, int8_t );

#endif //AVR_CLION_LOGGER_H
