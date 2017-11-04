#ifndef MAZENAV_ENCODER_READER_H
#define MAZENAV_ENCODER_READER_H

#include <stdint.h>

class EncoderReader {

public:
    EncoderReader(int interruptPinA, int interruptPinB, double resolution, double radius, int16_t encMask);
    void enable();
    void disable();
    void tick();
    double getDistance();
    double getDeltaDistance();

    volatile long ticks;
    volatile long oldTicks;
    volatile unsigned long time;
    volatile double angularSpeed;
    const double resolution;
    const double radius;

    void (*isr) (void);
        
private:
    
    const int8_t lookup_table[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    const int16_t pinMask;
    volatile int16_t prevState;
    const int interruptPinA;
    const int interruptPinB;

    
};

#endif