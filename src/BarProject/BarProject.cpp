#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "DistanceSensor.h"
#include "IRSensor.h"
#include "Navigator.h"
#include "WallDetector.h"
#include "Search.h"
#include "MappingStrategy.h"
#include "WifiConnection.h"
#include "TCPServer.h"
#include "Led.h"

int encoderResolution = 904.0;
double wheelRadius = 0.021; //m
int initialPwm = 70;
int isWifiEnabledPin = 48;
int wifiEnabled = 0;
bool shouldMap = true;

Led led(46);

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
HashMap<Tile*> * maze = new HashMap<Tile*>();

WifiConnection conn;
Command command;
TCPServer server(4420,&command);
String serverIP = "UNDEFINED";
int serverPort = 4421;

long time = 0;

static void leftIsr() {
	leftEncoder.tick();	
}

static void rightIsr() {
	rightEncoder.tick();	
}

void setup() {	
	Serial.begin(9600);
	pinMode(isWifiEnabledPin,INPUT_PULLUP);
	Serial.println("Radio Live Transmission...");
	delay(3000);
	conn.Begin();
	server.begin();
	leftEncoder.isr = &leftIsr;
	rightEncoder.isr = &rightIsr;
	navigator.initialMosh = initialPwm;


	navigator.enableEncoders();
	speedControl.enable(0);
	
}

void loop() {	

	wifiEnabled = digitalRead(isWifiEnabledPin);
	if(wifiEnabled)
	{
		led.enable();
		server.wait4Command();
		if(command.type != UNDEFINED)
		{
			led.disable();
			if(command.type == MAP_MAZE)
			{
				
				if(maze != nullptr)
				{
					//todo: eliminar los tiles cada vez que se crea un nuevo mapa
					delete maze;
				}
				maze = new HashMap<Tile*>();
				MappingStrategy mapper(maze, &frontWallDetector, &leftWallDetector, &rightWallDetector, &navigator);
				Tile* t = mapper.init(DIRECTION_N);
				for (; t != nullptr; t = mapper.step(t));
				led.blink(5);
			}
			else if(command.type == SEARCH)
			{
				Tile * startTile = maze->get(command.startTile.c_str());
				Tile * goalTile = maze->get(command.goalTile.c_str());
				if(startTile != nullptr && goalTile != nullptr)
				{
					Queue<int> route;
					if(command.searchAlg = DFS)
						Search::dfs(startTile, goalTile, &route);
					else if(command.searchAlg == BFS)
						Search::bfs(startTile, goalTile, &route);
					else if(command.searchAlg == ASTAR)
						Search::astar(startTile, goalTile, &route);
					else
						led.blink(3);

					if(!route.isEmpty())
					{
						Serial.print("Facing:");
						Serial.println(navigator.facing);
						Serial.print("Route: ");
						route.print();
						navigator.executeRoute(&route);
					}
				}
				else 
					led.blink(2);
			} 
			else if(command.type == SET_IP)
			{
				serverIP = command.serverIP;
			}
			command.type = UNDEFINED;
		}	
	}
	else
	{
		if(shouldMap)
		{
			Serial.println("MODAFOCAAAA");
		}
	}
	//testContinuousWallDetection(&frontWallDetector, &rightWallDetector, &leftWallDetector, &navigator, &props);
	
	//motorsSimpleTest(leftMotor, rightMotor);
	
}
