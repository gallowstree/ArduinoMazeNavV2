#ifndef MAZENAV_ENCODER_READER_H
#define MAZENAV_ENCODER_READER_H

class EncoderReader {

public:
    EncoderReader(int interruptPinA, int interruptPinB, int resolution, double radius);
    void enable(void (*isr) (void));
    void disable();
    void isr();
    double getDistance();

    volatile int ticks;
    volatile int oldTicks;
    volatile unsigned long time;
    volatile double angularSpeed;
    
    volatile int isrCounter = 0; 
private:
    
    
    const int interruptPinA;
    const int interruptPinB;
    const int resolution;
    const double radius;
};

#endif