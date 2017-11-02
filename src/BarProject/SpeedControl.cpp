#include "SpeedControl.h"
#include <Arduino.h>
#include <math.h>

SpeedControl::SpeedControl(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor) :
leftEncoder(leftEncoder),
rightEncoder(rightEncoder),
leftMotor(leftMotor),
rightMotor(rightMotor)
{
}

void SpeedControl::enable() {
    //Serial.println("enabling speedctl");
    enabled = true;
    posX = 0;
    posY = 0;
    theta = 0;
    error = 0;
    sumError =0;
    deltaError = 0;
    lastError = 0;
}

void SpeedControl::disable() {
    //Serial.println("disabling speedctl");
    enabled = false;
}

void SpeedControl::updatePID() {
    if(time == 0) {
        time = millis();
    }

    int deltaTime = millis() - time;
    if(deltaTime > 20)
    {
        double dr = rightEncoder->getDeltaDistance();
        double dl = leftEncoder->getDeltaDistance();
        double dc = (dr+dl)/2;
        if(dc != 0)
        {
            double deltaX = dc * cos(theta);
            double deltaY = dc * sin(theta);
            
            posX += deltaX;
            posY += deltaY;

            double deltaTheta = (dr - dl)/wheelsDistance;

            theta += deltaTheta;

            error = refTheta - theta;
            sumError += error;

            deltaError = error - lastError;
            double output = kp*error + ki*(sumError*((deltaTime/1000.0))) + kd*(deltaError/(deltaTime/1000.0));
            lastError = error;

            double newLeft = 0;
            double newRight = 0;
            if (output < 0)
            {
                newLeft  =  leftMotor->getPulseLength()  + abs(output);	
                newRight =  rightMotor->getPulseLength() - abs(output);		
            }
            else
            {
                newLeft  =  leftMotor->getPulseLength()  - abs(output);	
                newRight =  rightMotor->getPulseLength() + abs(output);
            }

            if (newLeft > maxPwm) newLeft = maxPwm;	
            else if (newLeft < minPwm) newLeft = minPwm;

            if (newRight > maxPwm) newRight = maxPwm;	
            else if (newRight < minPwm) newRight = minPwm;	
          
            leftMotor->setPulseLength((int) ceil(newLeft));
            rightMotor->setPulseLength((int) ceil(newRight));

            Serial.print("x: ");
            Serial.print(posX);
            Serial.print(" ,y: ");
            Serial.print(posY);
            Serial.print(" , output: ");
            Serial.print(output);
            Serial.print(" , newLeft: ");
            Serial.print(newLeft);
            Serial.print(" , newRight: ");
            Serial.print(newRight);
            Serial.print(" ,error: ");
            Serial.println(error);
    
        }

        time = millis();
    }
}


