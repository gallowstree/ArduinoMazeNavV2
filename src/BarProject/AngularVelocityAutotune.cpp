#include "AngularVelocityAutotune.h"
#include "TwiddleAutotune.h"
#include <Arduino.h>

AngularVelocityAutotune::AngularVelocityAutotune(AngularVelocityControl* ctl) : 
ctl(ctl) {

}

 double AngularVelocityAutotune::iterate(double p[]) {
    ctl->kp = p[0];
    ctl->ki = p[1];
    ctl->kd = p[2];

    Serial.print("Iterating with p:");
    Serial.print(ctl->kp, 6);
    Serial.print(" i:");
    Serial.print(ctl->ki, 6);
    Serial.print(" d:");
    Serial.println(ctl->kd, 6);

    ctl->setpoint = targetVelocity;
    ctl->encoder->enable();
    ctl->enable(initialMosh);
    ctl->motor->move(Direction::FORWARD);

    long time = millis();

    while((millis() - time) < 5000);

    ctl->disable();
    ctl->motor->stop();
    ctl->encoder->disable();
    
    double avgError = ctl->error / ctl->samples;
    Serial.print("Avg. error: ");
    Serial.println(avgError);
    Serial.print("Avg. velocity: ");
    Serial.println(ctl->avgVelocity);
    Serial.println();
    
    return avgError;
}