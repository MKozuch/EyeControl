//
// Created by MKozuch on 2016-03-13.
//

#include "eyeControl_buffer.h"

int8_t eyeControl_buffer[BUFFERSIZE] = {0};
uint8_t buffer_i = 0;

iterator buffer_iterator = eyeControl_buffer;

iterator buffer_begin = eyeControl_buffer;

iterator buffer_end = eyeControl_buffer + BUFFERSIZE;

iterator buffer_next()
{
    buffer_iterator += 1;
    if (buffer_iterator == buffer_end) buffer_iterator = buffer_begin;
    return buffer_iterator;
}

iterator buffer_previous()
{
    if (buffer_iterator == buffer_begin) buffer_iterator = buffer_end;
    buffer_iterator -= 1;
    return buffer_iterator;
}

int8_t buffer_addToBuffer(int8_t sample)
{
    *(buffer_next()) = sample;
    return sample;
}

iterator buffer_oldestElement()
{
    iterator oldest = (buffer_iterator+1);
    if (oldest > buffer_end) oldest = buffer_begin;
    return oldest;
}



