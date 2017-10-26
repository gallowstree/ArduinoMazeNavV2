#include "IRSensor.h"
#include <Arduino.h>

IRSensor::IRSensor(int inPin) :
    inPin(inPin){
    pinMode(inPin, INPUT);
}

bool IRSensor::ObstacleDetected()
{
    return !digitalRead(inPin);
}
