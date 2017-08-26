#include "EncoderReader.h"
#include <Arduino.h>

EncoderReader::EncoderReader(int interruptPinA, int interruptPinB, int resolution, double radius) :
interruptPinA(interruptPinA),
interruptPinB(interruptPinB),
resolution(resolution),
radius(radius)
{

}

void EncoderReader::enable(void (*isr) (void)) {
    ticks = 0;
    time = 0;
    oldTicks = 0;
    angularSpeed = 0;
    attachInterrupt(digitalPinToInterrupt(interruptPinA), isr, RISING);  
    attachInterrupt(digitalPinToInterrupt(interruptPinB), isr, RISING);  
}

void EncoderReader::disable() {
    detachInterrupt(digitalPinToInterrupt(interruptPinA));
    detachInterrupt(digitalPinToInterrupt(interruptPinB));
}

void EncoderReader::isr() {
    if(time == 0)
    {
        time = millis();
    }

    if (digitalRead(interruptPinA) == HIGH && digitalRead(interruptPinB) == LOW) {
        ticks++;
    }
    else if (digitalRead(interruptPinB) == HIGH && digitalRead(interruptPinA) == LOW) {
        ticks--;
    }

    int diffTime = millis() - time;
    if(diffTime >= 10)
    {
        angularSpeed = (((abs(ticks) - oldTicks) / resolution) * TWO_PI) / diffTime;
        time = millis();
        oldTicks = abs(ticks);
        isrCounter++;
    }
}

double EncoderReader::getDistance() {
    return TWO_PI * radius * (abs(ticks) / resolution);
}