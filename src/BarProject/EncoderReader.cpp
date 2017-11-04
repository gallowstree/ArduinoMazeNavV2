#include "EncoderReader.h"
#include <Arduino.h>

EncoderReader::EncoderReader(int interruptPinA, int interruptPinB, double resolution, double radius, int16_t pinMask) :
interruptPinA(interruptPinA),
interruptPinB(interruptPinB),
resolution(resolution),
radius(radius),
pinMask(pinMask)
{

}

void EncoderReader::enable() {
    ticks = 0;
    time = 0;
    oldTicks = 0;
    angularSpeed = 0;
    prevState = 0;
    attachInterrupt(digitalPinToInterrupt(interruptPinA), isr, CHANGE);  
    attachInterrupt(digitalPinToInterrupt(interruptPinB), isr, CHANGE);  
}

void EncoderReader::disable() {
    detachInterrupt(digitalPinToInterrupt(interruptPinA));
    detachInterrupt(digitalPinToInterrupt(interruptPinB));
}

void EncoderReader::tick() 
{
    prevState = prevState << 2;
    prevState = prevState | ((PIND & pinMask) >> ( pinMask == 0x0003 ? 0 : 2)); //Left encoder doesn't need right-shift 
 
    ticks += lookup_table[prevState & 0b1111];    
}

double EncoderReader::getDistance() {
    return TWO_PI * radius * ticks / resolution;
}

double EncoderReader::getDeltaDistance() {
    double deltaDistance = TWO_PI * radius * (ticks - (oldTicks)) / resolution;
    oldTicks = ticks;
    return deltaDistance;
}