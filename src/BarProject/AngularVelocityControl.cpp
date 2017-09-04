#include "AngularVelocityControl.h"
#include <Arduino.h>
#include <math.h>

AngularVelocityControl::AngularVelocityControl(EncoderReader* encoder, DcMotor* motor) :
encoder(encoder),
motor(motor),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT)
 {
    myPID.SetSampleTime(20);
    myPID.SetOutputLimits(-10, 10);
}

void AngularVelocityControl::enable() {
    Serial.println("enabling speedctl");
    enabled = true;
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void AngularVelocityControl::disable() {
    Serial.println("disabling speedctl");
    myPID.SetMode(MANUAL);
    enabled = false;
}

void AngularVelocityControl::updatePID() {    

    if (!enabled ) 
        return;
    
    input = encoder->angularSpeed;
    
    if (!myPID.Compute()) 
        return;    

    auto newLeft = motor->getPulseLength() + output;

    if (newLeft > maxPwm) newLeft = maxPwm;
    else if (newLeft < minPwm) newLeft = minPwm;    
    
    motor->setPulseLength((int) ceil(newLeft));    
    
    Serial.print(" i: ");
    Serial.print(input);
    Serial.print(" o: ");
    Serial.print(output);
    Serial.print(" new: ");
    Serial.println(newLeft);
        
}

