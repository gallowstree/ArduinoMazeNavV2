#ifndef MAZENAV_SELF_TESTS_H
#define MAZENAV_SELF_TESTS_H

#include "DcMotor.h"
#include "EncoderReader.h"
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