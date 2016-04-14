//
// Created by MKozuch on 2016-03-13.
//

/*******************************************************
 *        NOT implemented - nothing to see here        *
 *******************************************************/

#include <stdint.h>

#ifndef AVR_CLION_EYECONTROL_FILTER_H
#define AVR_CLION_EYECONTROL_FILTER_H

#define FILTERLENGTH 2
#define FILTERCOEFFS {1, 1}

int8_t filter_buffer[FILTERLENGTH];


#endif //AVR_CLION_EYECONTROL_FILTER_H
