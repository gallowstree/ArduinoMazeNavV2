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
#endif