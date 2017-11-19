#include <Arduino.h>
#include "Maze.h"
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "DistanceSensor.h"
#include "IRSensor.h"
#include "Navigator.h"
#include "WallDetector.h"
#include "Search.h"
#include "MappingStrategy.h"

int encoderResolution = 904.0;
double wheelRadius = 0.021; //m
int initialPwm = 70;
Maze* maze = new Maze(3,2);
bool searchRoute = true;
Queue<int> route;

int currDir = 3;

EncoderReader leftEncoder(20, 21, encoderResolution, wheelRadius, 0x0003);
EncoderReader rightEncoder(18, 19, encoderResolution, wheelRadius, 0x000C);

DcMotor leftMotor(A1, A0, 4, initialPwm, 4.66, 78.43, 0.07);
DcMotor rightMotor(A2, A3, 3, initialPwm, 4.39, 461.86, 0.01);

SpeedControl speedControl(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor);
Navigator navigator(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor, &speedControl);

IRSensor leftSensor(50);
IRSensor rightSensor(51);
IRSensor frontSensor(53);

//DistanceSensor frontSensor(50, 52);
WallDetector frontWallDetector(&frontSensor);
WallDetector rightWallDetector(&rightSensor);
WallDetector leftWallDetector(&leftSensor);


long time = 0;

static void leftIsr() {
	leftEncoder.tick();	
}

static void rightIsr() {
	rightEncoder.tick();	
}

void setup() {	
	Serial.begin(9600);
	Serial.println("Radio Live Transmission...");
	
	delay(3000);
	leftEncoder.isr = &leftIsr;
	rightEncoder.isr = &rightIsr;
	navigator.initialMosh = initialPwm;


	navigator.enableEncoders();
	speedControl.enable(0);
	
	//testConstants();
	
	MappingStrategy mapper(&frontWallDetector, &leftWallDetector, &rightWallDetector, &navigator);
	mapper.init();
}

void clearRoute() {
    while (!route.isEmpty())
        route.dequeue();
}

void loop() {	


	//testContinuousWallDetection(&frontWallDetector, &rightWallDetector, &leftWallDetector, &navigator, &props);
	
	//motorsSimpleTest(leftMotor, rightMotor);
	
}
