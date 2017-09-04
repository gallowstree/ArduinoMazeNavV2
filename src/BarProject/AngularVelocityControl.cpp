#include "AngularVelocityControl.h"
#include <Arduino.h>
#include <math.h>

AngularVelocityControl::AngularVelocityControl(EncoderReader* encoder, DcMotor* motor) :
encoder(encoder),
motor(motor),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT),
error(0)
 {
    myPID.SetSampleTime(20);
    myPID.SetOutputLimits(-10, 10);
}

void AngularVelocityControl::enable(int initialMosh) {
    motor->setPulseLength(initialMosh);
    error = 0;
    samples = 0;
    Serial.print("enabling speedctl... initial mosh: ");
    Serial.println(initialMosh);
    enabled = true;
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void AngularVelocityControl::disable() {
    Serial.println("disabling speedctl");
    myPID.SetMode(MANUAL);
    enabled = false;
    avgVelocity /= samples;
}

void AngularVelocityControl::updatePID() {    

    if (!enabled ) 
        return;
    
    input = encoder->angularSpeed;
    
    if (!myPID.Compute()) 
        return;    

    auto newLeft = motor->getPulseLength() + output;
    error += abs(setpoint - input);
    samples++;
    avgVelocity += input;

    if (newLeft > maxPwm) newLeft = maxPwm;
    else if (newLeft < minPwm) newLeft = minPwm;    
    
    motor->setPulseLength((int) ceil(newLeft));    
        
}

