#include <Arduino.h>
#include "Maze.h"
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "DistanceSensor.h"
#include "IRSensor.h"
#include "Navigator.h"
#include "WallDetector.h"
#include "MazeProperties.h"
#include "Search.h"

int encoderResolution = 230;
double wheelRadius = 0.021; //m
int initialPwm = 75;
Maze* maze = new Maze(3,2);
bool searchRoute = true;
Queue<int> route;

int currDir = 3;

EncoderReader leftEncoder(21, 20, encoderResolution, wheelRadius);
EncoderReader rightEncoder(18, 19, encoderResolution, wheelRadius);

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

	maze->startTile = maze->getTileAt(0,1);
	maze->goalTile = maze->getTileAt(2,0);

	navigator.enableEncoders();
	speedControl.enable();

	maze->getTileAt(0,1)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(1,1)->hasWallAt[DIRECTION_UP] = true;
	maze->getTileAt(1,0)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(2,0)->hasWallAt[DIRECTION_UP] = true;
	//testConstants();	
}

void clearRoute() {
    while (!route.isEmpty())
        route.dequeue();
}

void loop() {	
	//testIRSensors(&frontSensor, &rightSensor, &leftSensor);
	//Serial.print("ki: ");
	//speedControl.ki++;
	//Serial.println(speedControl.ki);
	navigator.move(props.tileSize - props.tileBorder, Direction::FORWARD);
	delay(1000);
	//motorsSimpleTest(leftMotor,rightMotor);
	//testContinuousWallDetection(&frontWallDetector, &rightWallDetector, &leftWallDetector, &navigator, &props);
	/*if (searchRoute)
	{
		Search::bfs(maze,&route);
		int nextDir = 0;
		while(!route.isEmpty())
		{
			nextDir = route.dequeue();
			if (currDir != nextDir)
				navigator.rotate(abs(navigator.changeDir[currDir][nextDir]), navigator.changeDir[currDir][nextDir] > 0 );
			
			currDir = nextDir;
			navigator.move(props.tileSize - props.tileBorder, Direction::FORWARD);
		}
		//
		//route.print();
		//maze->resetVisitedTiles();
		//clearRoute();
		//Serial.print(navigator.changeDir[DIRECTION_DOWN][DIRECTION_UP]);
		Serial.println("DONE!");
		searchRoute = false;
	}*/
}
