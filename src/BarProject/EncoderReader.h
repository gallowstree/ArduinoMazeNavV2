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

    

private:
    volatile unsigned long time;
    
    const int interruptPinA;
    const int interruptPinB;
    const int resolution;
    const double radius;
};

#endif