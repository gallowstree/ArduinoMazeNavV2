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
void Navigator::move(double distanceMeters, Direction direction) {        
    enableEncoders();
    speedControl->enable(0);
    startMotors(direction);
    waitForDistance(distanceMeters);
    stop();
}

void Navigator::rotate(double degrees) {
    if (degrees == 0) 
        return;

    double rads = degrees * TWO_PI / 360.0f;    
    double targetDistance = rads * rotationRadius;
    
    enableEncoders();
    speedControl->enable(rads);

    leftMotor->setPulseLength(rotationMosh);
    rightMotor->setPulseLength(rotationMosh);
    
    leftMotor->move((degrees > 0) ? Direction::FORWARD : Direction::BACKWARDS);
    rightMotor->move((degrees < 0) ? Direction::FORWARD : Direction::BACKWARDS);
    while ((degrees < 0) ? speedControl->theta <= 0 : speedControl->theta >= 0 ) {
        speedControl->updatePID(false);
    }
    stop();
}

void Navigator::executeRoute(Queue<int> *route) {    
    while(!route->isEmpty()) {
        int nextDir = route->dequeue();
        if (facing != nextDir)
            faceDirection(nextDir);
        
        facing = nextDir;
        move(props.tileSize - props.tileBorder, Direction::FORWARD);
    }
}

void Navigator::faceDirection(int direction) {
    rotate(changeDir[facing][direction]);
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
    while (speedControl->posX <= distanceMeters) {
        speedControl->updatePID(true);
    }
}