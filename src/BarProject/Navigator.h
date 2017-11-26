#ifndef MAZENAV_NAVIGATOR_H
#define MAZENAV_NAVIGATOR_H

#include "EncoderReader.h"
#include "DcMotor.h"
#include "SpeedControl.h"
#include "MazeProperties.h"
#include "Queue.h"

#define DIRECTION_W 0
#define DIRECTION_N 1
#define DIRECTION_E 2
#define DIRECTION_S 3

class Navigator {
public:
    Navigator(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor, SpeedControl* speedControl);

    EncoderReader* leftEncoder;
    EncoderReader* rightEncoder;

    DcMotor* leftMotor;
    DcMotor* rightMotor;

    SpeedControl* speedControl;

    int facing = DIRECTION_N;

    //cm between wheels
    double rotationRadius = 5.2;

    //Always reset mosh to this value after moving, it is set in BarProject.cpp
    int initialMosh = 35;

    //Need more strength when rotating
    int leftRotationMosh = 52;
    int rightRotationMosh = 44;

    int const changeDir[4][4] = { {0,90,180,-90}, //FACING LEFT
                                  {-90,0,90,180}, //FACING UP
                                  {180,-90,0,90}, //FACING RIGHT 
                                  {90,180,-90,0}  //FACING DOWN
                                };
    
    void faceDirection(int direction);
    void move(double distanceCm, Direction direction);
    void rotate(double degrees);
    void enableEncoders();
    void executeRoute(Queue<int> *route);
private:
    void startMotors(Direction direction);
    void stop();
    void waitForDistance(double distanceCm);
    MazeProperties props;
};

#endif