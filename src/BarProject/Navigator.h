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

    int const changeDir[4][4] = { {0,90,180,-90}, //FACING LEFT
                                  {-90,0,90,180}, //FACING UP
                                  {180,-90,0,90}, //FACING RIGHT 
                                  {90,180,-90,0}  //FACING DOWN
                                };
    
    void move(double distanceCm, Direction direction);
    void rotate(double degrees, bool clockwise);
    void enableEncoders();
private:
    void startMotors(Direction direction);
    void stop();
    void waitForDistance(double distanceCm);
};

#endif