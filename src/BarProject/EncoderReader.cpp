#include "EncoderReader.h"
#include <Arduino.h>

EncoderReader::EncoderReader(int interruptPinA, int interruptPinB, double resolution, double radius) :
interruptPinA(interruptPinA),
interruptPinB(interruptPinB),
resolution(resolution),
radius(radius)
{

}

void EncoderReader::enable() {
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

bool EncoderReader::tick() {
    bool shouldUpdateSpeed = false;

    if(time == 0) {
        time = millis();
    }

    if (digitalRead(interruptPinA) == HIGH && digitalRead(interruptPinB) == LOW) {
        ticks++;
        shouldUpdateSpeed = true;
    }
    else if (digitalRead(interruptPinB) == HIGH && digitalRead(interruptPinA) == LOW) {
        ticks++;
        shouldUpdateSpeed = true;
    }

    int diffTime = millis() - time;

    if (shouldUpdateSpeed && diffTime >= 10) {
        double diffAngle = (((abs(ticks) - oldTicks) / resolution) * TWO_PI);
        angularSpeed = diffAngle / (diffTime / 1000.0);
        time = millis();
        oldTicks = abs(ticks);          
        return true;
    }
    return false;
}

double EncoderReader::getDistance() {
    return TWO_PI * radius * (abs(ticks) / resolution);
}