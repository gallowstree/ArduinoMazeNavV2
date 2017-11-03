#include "Navigator.h"
#include <Arduino.h>
#include <math.h>

Navigator::Navigator(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor, SpeedControl* speedControl) : 
leftEncoder(leftEncoder),
rightEncoder(rightEncoder),
leftMotor(leftMotor),
rightMotor(rightMotor),
speedControl(speedControl) {

}

//Maybe look for negative acceleration to startk braking after passing through the center of the square
void Navigator::move(double distanceCm, Direction direction) {        
    enableEncoders();
    speedControl->enable(0);
    startMotors(direction);
    waitForDistance(distanceCm);
    stop();
}

void Navigator::rotate(double degrees, bool clockwise) {
    if (degrees == 0) 
        return;

    double rads = degrees * TWO_PI / 360.0f;    
    double targetDistance = rads * rotationRadius;
    
    enableEncoders();
    speedControl->enable(rads);

    leftMotor->setPulseLength(rotationMosh);
    rightMotor->setPulseLength(rotationMosh);
    
    leftMotor->move(clockwise ? Direction::FORWARD : Direction::BACKWARDS);
    rightMotor->move(!clockwise ? Direction::FORWARD : Direction::BACKWARDS);
    while (speedControl->theta < -0.10) {
        speedControl->updatePID();
    }
    stop();
}

void Navigator::enableEncoders() {
    leftEncoder->enable();
    rightEncoder->enable();
}

void Navigator::startMotors(Direction direction) {
    leftMotor->setPulseLength(initialMosh);
    rightMotor->setPulseLength(initialMosh);

    leftMotor->move(direction);
    rightMotor->move(direction);
}

void Navigator::stop() {
    leftMotor->stop();
    leftEncoder->disable();
    speedControl->disable();

    rightMotor->stop();
    rightEncoder->disable();
    speedControl->disable();
}

void Navigator::waitForDistance(double distanceMeters) {
    int targetTicks = (int) floor(distanceMeters / (TWO_PI * leftEncoder->radius) * leftEncoder->resolution);    
    double goalPosX = 0.21;
    while (speedControl->posX < goalPosX) {
        speedControl->updatePID();
        /*if (leftEncoder->ticks >= targetTicks) {
            leftMotor->stop();
            leftEncoder->disable();
            speedControl->disable();
        }  

        if (rightEncoder->ticks >= targetTicks) {
            rightMotor->stop();
            rightEncoder->disable();
            speedControl->disable();
        } */ 
    }
}