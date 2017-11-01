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
}

void SpeedControl::disable() {
    //Serial.println("disabling speedctl");
    enabled = false;
}

void SpeedControl::updatePID() {
    if(time == 0) {
        time = millis();
    }

    int diffTime = millis() - time;
    if(diffTime > 50)
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
            Serial.print("x: ");
            Serial.print(posX);
            Serial.print(" ,y: ");
            Serial.print(posY);
            Serial.print(" ,theta: ");
            Serial.print(theta);
            Serial.print(" ,error: ");
            Serial.println(error);
    
        }

        time = millis();
    }
}


