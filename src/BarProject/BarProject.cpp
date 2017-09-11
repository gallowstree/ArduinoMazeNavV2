#include <Arduino.h>
#include "DcMotor.h"
#include "SelfTests.h"
#include "SpeedControl.h"
#include "AngularVelocityControl.h"
#include "Navigator.h"
#include "AngularVelocityAutotune.h"

int encoderResolution = 230;
double wheelRadius = 2.1; //cm
int initialPwm = 60;

EncoderReader leftEncoder(21, 20, encoderResolution, wheelRadius);
EncoderReader rightEncoder(18, 19, encoderResolution, wheelRadius);

DcMotor leftMotor(A1, A0, 4, initialPwm);
DcMotor rightMotor(A2, A3, 3, initialPwm);

SpeedControl speedControl(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor);

AngularVelocityControl leftControl(&leftEncoder, &leftMotor);
AngularVelocityControl rightControl(&rightEncoder, &rightMotor);

Navigator navigator(&leftEncoder, &rightEncoder, &leftMotor, &rightMotor, &speedControl);

long time = 0;

static void leftIsr() {
	leftEncoder.tick();
	leftControl.updatePID();
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
	leftControl.enable(60);
	/*rightEncoder.enable();
	speedControl.enable();
	 */

	// rightControl.enable();
	// leftControl.enable();
	
	//AngularVelocityAutotune tune(&leftControl);
	//tune.start();

	//Serial.println("Tuning Done");
	
	time = millis();

}


void loop() {	
	leftEncoder.enable();
	leftMotor.move(FORWARD);
	delay(3000);
	leftEncoder.disable();
	
	 //testInterruptCounters(leftEncoder, rightEncoder);
	 /*Serial.print("rs: ");
	 Serial.print(rightEncoder.angularSpeed);
	 Serial.print("ls: ");
	 Serial.println(leftEncoder.angularSpeed);*/
	 
	 
	/*  
	delay(3000);
	navigator.move(50, Direction::FORWARD);
	delay(500);
	navigator.rotate(90, false);
	delay(500);
	navigator.move(23, Direction::FORWARD);
	 */


	//  int timeDiff = millis() - time;
	//  if (timeDiff > 2000) {
	// 	 time = millis();
	// 	 direction = direction == Direction::FORWARD ? Direction::BACKWARDS : Direction::FORWARD;
	// 	 leftMotor.move(direction);
	// 	 rightMotor.move(direction);
	//  }



	 //speedControl.updatePID();	 
}
