#ifndef MAZENAV_SELF_TESTS_H
#define MAZENAV_SELF_TESTS_H

#include "DcMotor.h"
#include "EncoderReader.h"
#include "Navigator.h"
#include "MazeProperties.h"
#include "WallDetector.h"
#include <Arduino.h>

void motorsSimpleTest(DcMotor& l, DcMotor& r) {
    int moveDelay = 2000;
    int stopDelay = 1000;

    l.move(Direction::FORWARD);
    r.move(Direction::FORWARD);    
    delay(moveDelay);    

    l.stop();
    r.stop();
    delay(stopDelay);

    l.move(Direction::BACKWARDS);
    r.move(Direction::BACKWARDS);    
    delay(moveDelay);
    
    l.stop();
    r.stop();
    delay(stopDelay);

    l.move(Direction::FORWARD);
    r.move(Direction::BACKWARDS);
    delay(moveDelay);     

    l.stop();
    r.stop();
    delay(stopDelay);

    l.move(Direction::BACKWARDS);
    r.move(Direction::FORWARD);
    delay(moveDelay);    
    
    l.stop();
    r.stop();    
}

int lticks = 0;
int rticks = 0;
void testInterruptCounters(EncoderReader& l, EncoderReader& r) {
    if (l.ticks != lticks || r.ticks != rticks ) {
        Serial.print("L: ");
        Serial.print(l.ticks);
        Serial.print(" R: ");
        Serial.println(r.ticks);
        lticks = l.ticks;
        rticks = r.ticks;
    }

    
}

/* This will move forward one square at a time. It will look for a wall 
in front of the robot, If there is no wall, it will keep  going forward.
This will return once we face  a wall and will always  leave  the robot
facing in  a direction where there is no wall. It will always check the
right first, if there is a wall, then try left. If there is also a wall,
face back to  where  we  came from.  If this function  is run in a loop,
it should give the robot continuous motion through a bounded path. */
void testContinuousWallDetection(WallDetector* detector, Navigator* navigator, MazeProperties* props) {  
    const int delayMs = 500;  
    while (!detector->isFacingWall()) {        
        navigator->move(props->tileSize - props->tileBorder, Direction::FORWARD);
        delay(delayMs);        
    }    
    
    int rotationCount = 0;
    while (detector->isFacingWall()) {
        navigator->rotate(90 * ( (rotationCount % 2) + 1 ) , rotationCount < 2);  
        rotationCount++;
        delay(delayMs);      
    }
}

// void testTimePerTick() {
//     rightEncoder.enable(&rightIsr);	
// 	rightMotor.move(Direction::FORWARD);
	
// 	leftEncoder.enable(&leftIsr);
// 	leftMotor.move(Direction::FORWARD);
	
	

// 	delay(10000);

// 	Serial.print("L: ");
// 	Serial.print(leftEncoder.ticks);
// 	Serial.print(" ");
// 	Serial.print(leftEncoder.time);

// 	Serial.print(" R: ");
// 	Serial.print(rightEncoder.ticks);
// 	Serial.print(" ");
// 	Serial.println(rightEncoder.time);

// 	rightMotor.stop();
// 	rightEncoder.disable();

// 	leftMotor.stop();	
// 	leftEncoder.disable();
	

// 	delay(3000);
// }
#endif