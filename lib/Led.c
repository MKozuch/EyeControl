#include "Led.h"
#include <avr/io.h>

#define LEFT_PIN PB1
#define REST_PIN PB0
#define RIGHT_PIN PB2
#define BLINK_PIN PB4

#define HEARTBEAT_PIN PB5

char led_setup(){
    DDRB |= (1<<LEFT_PIN) | (1<<REST_PIN) | (1<<RIGHT_PIN) | (1<<BLINK_PIN);
    PORTB &= ~((1<<LEFT_PIN) | (1<<REST_PIN) | (1<<RIGHT_PIN) | (1<<BLINK_PIN));
    return 0;
}


char led_on(LedName led){
    switch (led){
        case LEFTLED:
            PORTB |= (1<<LEFT_PIN);
            break;
        case RIGHTLED:
            PORTB |= (1<<RIGHT_PIN);
            break;
        case RESTLED:
            PORTB |= (1<<REST_PIN);
            break;
        case BLINKLED:
            PORTB |= (1<<BLINK_PIN);
            break;
        default:
            PORTB |= ((1<<LEFT_PIN) | (1<<REST_PIN) | (1<<RIGHT_PIN) | (1<<BLINK_PIN));
            break;
    }
    return 0;
}


char led_off(LedName led){
    switch (led){
        case LEFTLED:
            PORTB &= ~(1<<LEFT_PIN);
            break;
        case RIGHTLED:
            PORTB &= ~(1<<RIGHT_PIN);
            break;
        case RESTLED:
            PORTB &= ~(1<<REST_PIN);
            break;
        case BLINKLED:
            PORTB &= ~(1<<BLINK_PIN);
            break;
        default:
            PORTB &= ~((1<<LEFT_PIN) | (1<<REST_PIN) | (1<<RIGHT_PIN) | (1<<BLINK_PIN));
            break;
    }
    return 0;
}


char led_switch(LedName led){
    switch (led){
        case LEFTLED:
            PORTB ^= (1<<LEFT_PIN);
            break;
        case RIGHTLED:
            PORTB ^= (1<<RIGHT_PIN);
            break;
        case RESTLED:
            PORTB ^= (1<<REST_PIN);
            break;
        case BLINKLED:
            PORTB ^= (1<<BLINK_PIN);
            break;
        default:
            break;
    }
    return 0;
}


int8_t led_heartbeatInit()
{
    DDRB |= (1<<HEARTBEAT_PIN);
    PORTB |= (1<<HEARTBEAT_PIN);
    return 0;
}

int8_t led_hearbeat()
{
    PORTB ^= (1<<HEARTBEAT_PIN);
    return 0;
}