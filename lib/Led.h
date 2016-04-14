#include <stdint.h>

#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

typedef enum ledname {RESTLED, LEFTLED, RIGHTLED, BLINKLED, ALLLED} LedName;

char led_setup();
char led_on(LedName);
char led_off(LedName);
char led_switch(LedName);

int8_t led_heartbeatInit();
int8_t led_hearbeat();

#endif // LED_H_INCLUDED
