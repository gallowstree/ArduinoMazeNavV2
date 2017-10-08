#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "DistanceSensor.h"
#include "Navigator.h"
#include "WallDetector.h"
#include "MazeProperties.h"
#include "Maze.h"
#include "Search.h"

int encoderResolution = 230;
double wheelRadius = 2.1; //cm
int initialPwm = 65;
Maze* maze = new Maze(5,5);
bool searchRoute = true;
Queue<int> route;

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

	maze->startTile = maze->getTileAt(0,0);
	maze->goalTile = maze->getTileAt(3,3);

	/*maze->getTileAt(0,0)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(1,0)->hasWallAt[DIRECTION_UP] = true;
	maze->getTileAt(1,1)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(2,1)->hasWallAt[DIRECTION_UP] = true;*/
	//testConstants();	
}

void clearRoute() {
    while (!route.isEmpty())
        route.dequeue();
}

void loop() {	
	//testContinuousWallDetection(&wallDetector, &navigator, &props);
	
	if (searchRoute)
	{
		Search::bfs(maze,&route);
		route.print();
		maze->resetVisitedTiles();
		clearRoute();
		Serial.println("shitafoca");
		searchRoute = false;
	}
}
