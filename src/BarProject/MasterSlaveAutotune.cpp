#include "MasterSlaveAutotune.h"
#include "TwiddleAutotune.h"
#include <Arduino.h>

MasterSlaveAutotune::MasterSlaveAutotune(MasterSlaveSpeedControl* ctl) : 
ctl(ctl) {

}

 double MasterSlaveAutotune::iterate(double p[]) {
    ctl->kp = p[0];
    ctl->ki = p[1];
    ctl->kd = p[2];

    Serial.print("Iterating with p:");
    Serial.print(ctl->kp, 8);
    Serial.print(" i:");
    Serial.print(ctl->ki, 8);
    Serial.print(" d:");
    Serial.println(ctl->kd, 8);

    ctl->setpoint = targetVelocity;
    ctl->masterEncoder->enable();
    ctl->slaveEncoder->enable();
    ctl->enable(initialMosh);    
    ctl->masterMotor->move(Direction::FORWARD);
    ctl->slaveMotor->move(Direction::FORWARD);

    long time = millis();

    while((millis() - time) < 5000);

    ctl->disable();
    ctl->masterEncoder->disable();
    ctl->slaveEncoder->disable();
    ctl->masterMotor->stop();
    ctl->slaveMotor->stop();    
    
    double avgError = ctl->error / ctl->samples;
    Serial.print("Avg. error: ");
    Serial.println(avgError);
    Serial.print("Avg. velocity: ");
    Serial.println(ctl->avgVelocity);
    Serial.println();

    delay(1000);
    
    return avgError;
}