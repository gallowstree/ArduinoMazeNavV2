#include "MotorDriver.h"

MotorDriver::MotorDriver() {
	pinMode(right0, OUTPUT);
    pinMode(right1, OUTPUT);
    pinMode(left0, OUTPUT);
    pinMode(left1, OUTPUT);
    pinMode(rightPwm, OUTPUT);
    pinMode(leftPwm, OUTPUT);

    analogWrite(rightPwm, (int) (pulseLength * pulseFraction));
    analogWrite(leftPwm, (int) (pulseLength * pulseFraction));
}

void MotorDriver::stop()
{
	Serial.println("stop");
	digitalWrite(right0, LOW);
    digitalWrite(right1, LOW);
    digitalWrite(left0, LOW);
    digitalWrite(left1, LOW);
}

void MotorDriver::moveForward()
{
	Serial.println("moveForward");
	digitalWrite(right0, HIGH);
    digitalWrite(right1, LOW);
    digitalWrite(left0, HIGH);
    digitalWrite(left1, LOW);
}

void MotorDriver::moveBackwards()
{
	Serial.println("moveBackwards");
	digitalWrite(right0, LOW);
    digitalWrite(right1, HIGH);
    digitalWrite(left0, LOW);
    digitalWrite(left1, HIGH);
}

void MotorDriver::rotate(bool clockwise)
{
	Serial.println("rotate");
	digitalWrite(right0, clockwise ? HIGH : LOW);
    digitalWrite(right1, clockwise ? LOW : HIGH);
    digitalWrite(left0, clockwise ? LOW : HIGH);
    digitalWrite(left1, clockwise ? HIGH : LOW);
}