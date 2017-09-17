#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "DistanceSensor.h"
#include "Navigator.h"
#include "WallDetector.h"
#include "MazeProperties.h"

int encoderResolution = 230;
double wheelRadius = 2.1; //cm
int initialPwm = 65;

EncoderReader leftEncoder(21, 20, encoderResolution, wheelRadius);
EncoderReader rightEncoder(18, 19, encoderResolution, wheelRadius);

DcMotor leftMotor(A1, A0, 4, initialPwm, 4.66, 78.43, 0.07);
DcMotor rightMotor(A2, A3, 3, initialPwm, 4.39, 461.86, 0.01);

SpeedControl speedControl(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor);
Navigator navigator(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor, &speedControl);

DistanceSensor frontSensor(50, 52);
WallDetector wallDetector(&frontSensor);
MazeProperties props;

long time = 0;

static void leftIsr() {
	leftEncoder.tick();	
}

static void rightIsr() {
	rightEncoder.tick();	
}

void testConstants() {
	leftEncoder.enable();
	rightEncoder.enable();

	leftMotor.move(Direction::FORWARD);
	rightMotor.move(Direction::FORWARD);

	speedControl.enable();
}

void setup() {	
	Serial.begin(9600);
	Serial.println("Radio Live Transmission...");
	
	delay(3000);
	leftEncoder.isr = &leftIsr;
	rightEncoder.isr = &rightIsr;
	navigator.initialMosh = initialPwm;

	//testConstants();	
}


void loop() {	
	testContinuousWallDetection(&wallDetector, &navigator, &props);
}
