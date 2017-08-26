#include "EncoderReader.h"
#include <Arduino.h>

EncoderReader::EncoderReader(int interruptPinA, int interruptPinB, int resolution, int radius) :
interruptPinA(interruptPinA),
interruptPinB(interruptPinB),
resolution(resolution),
radius(radius)
{

}

void EncoderReader::enable(void (*isr) (void)) {
    ticks = 0;
    time = 0;
    attachInterrupt(digitalPinToInterrupt(interruptPinA), isr, RISING);  
    attachInterrupt(digitalPinToInterrupt(interruptPinB), isr, RISING);  
}

void EncoderReader::disable() {
    detachInterrupt(digitalPinToInterrupt(interruptPinA));
    detachInterrupt(digitalPinToInterrupt(interruptPinB));
}

void EncoderReader::isr() {
    if (digitalRead(interruptPinA) == HIGH && digitalRead(interruptPinB) == LOW) {
        ticks++;
    }
    else if (digitalRead(interruptPinB) == HIGH && digitalRead(interruptPinA) == LOW) {
        ticks--;
    }
}

double Encoder::getDistance() {
    return TWO_PI * radius * (abs(ticks) / resolution);
}