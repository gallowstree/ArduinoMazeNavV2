#ifndef MAZENAV_LED_H
#define MAZENAV_LED_H

#include <Arduino.h>

class Led {

public:
    Led(int outPin);
    void enable();
    void disable();
    void blink(int repeat);

private:
    const int outPin;
    
};

#endif