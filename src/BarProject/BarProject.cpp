#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"

DcMotor leftMotor(A1, A0, 2, 100);
DcMotor rightMotor(A2, A3, 3, 100);

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


}

void loop() {
	//motorsSimpleTest(leftMotor, rightMotor);	
	//testInterruptCounters(leftEncoder, rightEncoder);
	rightEncoder.enable(&rightIsr);	
	rightMotor.move(Direction::FORWARD);
	
	leftEncoder.enable(&leftIsr);
	leftMotor.move(Direction::FORWARD);
	
	// delay(500);

	// Serial.print("angular speed: ");
	// Serial.print();

	delay(10000);
	Serial.print("rCounter: ");
	Serial.print(rightEncoder.isrCounter);
	Serial.print(" Rtix: ");
	Serial.println(rightEncoder.ticks);

	Serial.print("lCounter: ");
	Serial.print(leftEncoder.isrCounter);
	Serial.print(" Ltix: ");
	Serial.println(leftEncoder.ticks);

	leftEncoder.disable();
	rightEncoder.disable();
}
