#include "SpeedControl.h"
#include <Arduino.h>
#include <math.h>

SpeedControl::SpeedControl(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor) :
leftEncoder(leftEncoder),
rightEncoder(rightEncoder),
leftMotor(leftMotor),
rightMotor(rightMotor),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT)
 {
    myPID.SetSampleTime(20);
    myPID.SetOutputLimits(-15, 15);
}

void SpeedControl::enable() {
    Serial.println("enabling speedctl");
    enabled = true;
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void SpeedControl::disable() {
    Serial.println("disabling speedctl");
    myPID.SetMode(MANUAL);
    enabled = false;
}

void SpeedControl::updatePID() {
    bool notReady = leftEncoder->angularSpeed * rightEncoder->angularSpeed == 0 &&
        leftEncoder->angularSpeed + rightEncoder->angularSpeed != 0;

    if (!enabled || notReady ) 
        return;

    double asl = leftEncoder->angularSpeed;
    double asr = rightEncoder->angularSpeed;
    //auto diff = leftEncoder->angularSpeed - rightEncoder->angularSpeed;
    auto diff = asl - asr;
    input = diff;
    
    if (!myPID.Compute()) 
        return;    

    output = abs(output);

    auto newLeft  =  leftMotor->getPulseLength()  + ( diff > 0 ? -(output) : output );
    auto newRight =  rightMotor->getPulseLength() + ( diff > 0 ? output : -(output) );

    if (newLeft > maxPwm) newLeft = maxPwm;
    else if (newLeft < minPwm) newLeft = minPwm;

    if (newRight > maxPwm) newRight = maxPwm;
    else if (newRight < minPwm) newRight = minPwm;
    
    leftMotor->setPulseLength((int) ceil(newLeft));
    rightMotor->setPulseLength((int) ceil(newRight));

    
    // Serial.print(" diff: ");
    // Serial.print(diff);
    // Serial.print(" output: ");
    // Serial.print(output);
    // Serial.print(" lv: ");
    // Serial.print(asl);
    // Serial.print(" rv: ");
    // Serial.print(asr);
    // Serial.print(" nl: ");
    // Serial.print(newLeft);
    // Serial.print(" nr: ");
    // Serial.println(newRight);

    
}

