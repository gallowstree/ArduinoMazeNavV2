#include "DcMotor.h"
#include <Arduino.h>

DcMotor::DcMotor(int out1, int out2, int pwmPin, int initialPulseLength, double kp, double kd, double ki) : 
out1(out1),
out2(out2),
pwmPin(pwmPin),
kp(kp),
kd(kd),
ki(ki),
pulseLength(initialPulseLength)
{
    pinMode(out1, OUTPUT);
    pinMode(out2, OUTPUT);
    pinMode(pwmPin, OUTPUT);    
    analogWrite(pwmPin, pulseLength);
}

void DcMotor::stop() {
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    //Should we reset the pulseLength?
}

void DcMotor::move(Direction direction) {
    bool forward = direction == Direction::FORWARD;
    digitalWrite(out1, forward ? HIGH : LOW);
    digitalWrite(out2, forward ? LOW  : HIGH);                
}

void DcMotor::setPulseLength(int p) {
    pulseLength = p; //maybe this variable is not needed
    //Serial.print("p")
    analogWrite(pwmPin, pulseLength);
}

int DcMotor::getPulseLength() {
    return pulseLength;
}

