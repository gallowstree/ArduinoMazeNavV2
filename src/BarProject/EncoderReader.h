#ifndef MAZENAV_ENCODER_READER_H
#define MAZENAV_ENCODER_READER_H

class EncoderReader {

public:
    EncoderReader(int interruptPinA, int interruptPinB, double resolution, double radius);
    void enable();
    void disable();
    void tick();
    double getDistance();

    volatile int ticks;
    volatile int oldTicks;
    volatile unsigned long time;
    volatile double angularSpeed;
    const double resolution;
    const double radius;

    void (*isr) (void);
        
private:
    
    
    const int interruptPinA;
    const int interruptPinB;
    
};

#endif