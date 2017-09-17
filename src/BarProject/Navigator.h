#ifndef MAZENAV_NAVIGATOR_H
#define MAZENAV_NAVIGATOR_H

#include "EncoderReader.h"
#include "DcMotor.h"
#include "SpeedControl.h"

class Navigator {
public:
    Navigator(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor, SpeedControl* speedControl);

    EncoderReader* leftEncoder;
    EncoderReader* rightEncoder;

    DcMotor* leftMotor;
    DcMotor* rightMotor;

    SpeedControl* speedControl;

    //cm between wheels
    double rotationRadius = 4;

    //Always reset mosh to this value after moving, it is set in BarProject.cpp
    int initialMosh = 70;

    //Need more strength when rotating
    int rotationMosh = 80;

    void move(double distanceCm, Direction direction);
    void rotate(double degrees, bool clockwise);
private:
    void enableEncoders();
    void startMotors(Direction direction);
    void stop();
    void waitForDistance(double distanceCm);
};

#endif