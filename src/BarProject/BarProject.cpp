#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"

DcMotor leftMotor(A1, A0, 2, 200);
DcMotor rightMotor(A2, A3, 3, 200);

int encoderResolution = 230;
double wheelRadius = 2.1; //cm

EncoderReader leftEncoder(21, 20, encoderResolution, wheelRadius);
EncoderReader rightEncoder(18, 19, encoderResolution, wheelRadius);

static void leftIsr() {
	leftEncoder.isr();
}

static void rightIsr() {
	rightEncoder.isr();
}

void setup() {	
	Serial.begin(9600);
	Serial.println("Radio Live Transmission...");
	
	delay(3000);

	leftEncoder.enable(&leftIsr);
	rightEncoder.enable(&rightIsr);
	
}

void loop() {
	//motorsSimpleTest(leftMotor, rightMotor);	
	testInterruptCounters(leftEncoder, rightEncoder);
}
