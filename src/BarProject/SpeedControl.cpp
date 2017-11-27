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

void SpeedControl::enable(double currentTheta) {
    //Serial.println("enabling speedctl");
    enabled = true;
    posX = 0;
    posY = 0;
    theta = currentTheta;
    error = 0;
    integral = 0;
    differential = 0;
    lastError = 0;
}

void SpeedControl::disable() {
    //Serial.println("disabling speedctl");
    enabled = false;
}

void SpeedControl::updatePID(bool adjustPWM) {
    if(time == 0) {
        time = millis();
    }

    int deltaTime = millis() - time;
    if(deltaTime > 20)
    {

        double dr = rightEncoder->getDeltaDistance();
        double dl = leftEncoder->getDeltaDistance();
        double dc = (dr+dl)/2;

        double deltaX = dc * cos(theta);
        double deltaY = dc * sin(theta);
            
        posX += deltaX;
        posY += deltaY;

        double deltaTheta = (dr - dl)/wheelsDistance;

        theta += deltaTheta;
        if(adjustPWM)
        {
            error = refTheta - theta;

            integral += error * (deltaTime/1000.0);
            differential = (error - lastError)/(deltaTime/1000.0);
            double output = kp*error + ki*integral + kd*differential;
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

          
            /*Serial.print("x: ");
            Serial.print(posX);
            Serial.print(" ,y: ");
            Serial.print(posY);
            Serial.print(" ,dc: ");
            Serial.print(dc);
            Serial.print(" ,theta: ");
            Serial.print(theta);
            Serial.print(" , output: ");
            Serial.print(output);
            Serial.print(" , newLeft: ");
            Serial.print(newLeft);
            Serial.print(" , newRight: ");
            Serial.print(newRight);
            Serial.print(" ,error: ");
            Serial.println(error);*/
            
        }
        time = millis();
    }
}


