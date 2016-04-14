//
// Created by MKozuch on 2016-02-25.
//

#include <stdint.h>

#ifndef AVR_CLION_BUTTON_H
#define AVR_CLION_BUTTON_H

typedef enum buttonname {BTNSEL, BTN3, BTN4, BTN5} ButtonName;

int8_t button_setup(ButtonName);
int8_t button_setupInterrupt(ButtonName);
int8_t button_getState(ButtonName);

#endif //AVR_CLION_BUTTON_H
