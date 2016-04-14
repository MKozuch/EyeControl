//
// Created by MKozuch on 2016-03-13.
//

#include <stdint.h>

#ifndef AVR_CLION_EYECONTROL_BUFFER_H
#define AVR_CLION_EYECONTROL_BUFFER_H

#define BUFFERLOGSIZE 5
#define BUFFERSIZE (1<<BUFFERLOGSIZE)

int8_t eyeControl_buffer[BUFFERSIZE];

int8_t buffer_addToBuffer(int8_t);

/* initializes buffer with zeros */
int8_t buffer_clearBuffer();

typedef int8_t* iterator;

iterator buffer_iterator;

/* points to the first element */
iterator buffer_begin;

/* points to the last plus one element */
iterator buffer_end;

/* move iterator to the next position and return */
iterator buffer_next();

/* move iterator back by one and return */
iterator buffer_previous();

/* return address of the oldest element in the buffer (the one after current element) */
iterator buffer_oldestElement();


#endif //AVR_CLION_EYECONTROL_BUFFER_H
