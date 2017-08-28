#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"

int encoderResolution = 230;
double wheelRadius = 2.1; //cm
int initialPwm = 90;

EncoderReader leftEncoder(21, 20, encoderResolution, wheelRadius);
EncoderReader rightEncoder(18, 19, encoderResolution, wheelRadius);

DcMotor leftMotor(A1, A0, 2, 60);
DcMotor rightMotor(A2, A3, 3, 250);

SpeedControl speedControl(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor);

static void leftIsr() {
	leftEncoder.tick();
	//speedControl.updatePID();
}

static void rightIsr() {
	rightEncoder.tick();
	//speedControl.updatePID();
}

void setup() {	
	Serial.begin(9600);
	Serial.println("Radio Live Transmission...");
	
	delay(3000);
	leftEncoder.isr = &leftIsr;
	rightEncoder.isr = &rightIsr;

	leftEncoder.enable();
	rightEncoder.enable();
	speedControl.enable();
	
	Serial.println("Setup Done");
	leftMotor.move(Direction::FORWARD);
	rightMotor.move(Direction::FORWARD);
}

void loop() {	
	 testInterruptCounters(leftEncoder, rightEncoder);
	 //speedControl.updatePID();
}
