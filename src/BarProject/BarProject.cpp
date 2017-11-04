#include <Arduino.h>
#include "Maze.h"
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "DistanceSensor.h"
#include "Navigator.h"
#include "WallDetector.h"
#include "MazeProperties.h"
#include "Search.h"

int encoderResolution = 230;
double wheelRadius = 2.1; //cm
int initialPwm = 70;
Maze* maze = new Maze(5,2);
bool searchRoute = true;
Queue<int> route;

int currDir = 3;

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

	maze->startTile = maze->getTileAt(3,1);
	maze->goalTile = maze->getTileAt(4,1);

	maze->getTileAt(0,1)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(1,1)->hasWallAt[DIRECTION_UP] = true;
	
	maze->getTileAt(1,0)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(2,0)->hasWallAt[DIRECTION_UP] = true;

	maze->getTileAt(3,0)->hasWallAt[DIRECTION_RIGHT] = true;
	maze->getTileAt(3,1)->hasWallAt[DIRECTION_LEFT] = true;

	maze->getTileAt(3,1)->hasWallAt[DIRECTION_DOWN] = true;
	maze->getTileAt(4,1)->hasWallAt[DIRECTION_UP] = true;
	//testConstants();	
}

void clearRoute() {
    while (!route.isEmpty())
        route.dequeue();
}

void solveMaze()
{
	if (searchRoute)
	{
		Search::bfs(maze,&route);
		int nextDir = 0;
		if (route.isEmpty())
		{
			navigator.rotate(360, true );	
		}
		else
		{
			while(!route.isEmpty())
			{
				nextDir = route.dequeue();
				if (currDir != nextDir)
					navigator.rotate(abs(navigator.changeDir[currDir][nextDir]) - 3, navigator.changeDir[currDir][nextDir] > 0 );
				
				currDir = nextDir;
				navigator.move(props.tileSize - props.tileBorder, Direction::FORWARD);
				delay(1000);
			}
			navigator.rotate(360, true );	
		}
		//
		//route.print();
		//maze->resetVisitedTiles();
		//clearRoute();
		//Serial.print(navigator.changeDir[DIRECTION_DOWN][DIRECTION_UP]);
		Serial.println("DONE!");
		searchRoute = false;
	}
}

void loop() {	
	//motorsSimpleTest(leftMotor,rightMotor);
	//testContinuousWallDetection(&wallDetector, &navigator, &props);
	solveMaze();
	// 
	// 
}
