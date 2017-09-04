#include "SpeedDifferenceAutotune.h"
#include "TwiddleAutotune.h"
#include <Arduino.h>

SpeedDifferenceAutotune::SpeedDifferenceAutotune(SpeedControl* ctl) : 
ctl(ctl) {

}

 double SpeedDifferenceAutotune::iterate(double p[]) {
    ctl->kp = p[0];
    ctl->ki = p[1];
    ctl->kd = p[2];

    Serial.print("Iterating with p:");
    Serial.print(ctl->kp, 6);
    Serial.print(" i:");
    Serial.print(ctl->ki, 6);
    Serial.print(" d:");
    Serial.println(ctl->kd, 6);

    ctl->setpoint = targetDifference;
    ctl->leftEncoder->enable();
    ctl->rightEncoder->enable();
    ctl->enable(initialMosh);
    ctl->leftMotor->move(Direction::FORWARD);
    ctl->rightMotor->move(Direction::FORWARD);

    long time = millis();

    while((millis() - time) < 5000);

    ctl->disable();
    ctl->leftMotor->stop();
    ctl->rightMotor->stop();
    ctl->leftEncoder->disable();
    ctl->rightEncoder->disable();
    
    double avgError = ctl->error / ctl->samples;
    Serial.print("Avg. error: ");
    Serial.println(avgError);
    Serial.print("Avg. velocity: ");
    Serial.println(ctl->avgVelocity);
    Serial.println();
    
    return avgError;
}