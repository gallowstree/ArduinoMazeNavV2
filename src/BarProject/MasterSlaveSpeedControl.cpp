#include "MasterSlaveSpeedControl.h"
#include <Arduino.h>

MasterSlaveSpeedControl::MasterSlaveSpeedControl(EncoderReader* masterEnc, EncoderReader* slaveEnc, DcMotor* masterMtr, DcMotor* slaveMtr) :
masterEncoder(masterEnc),
slaveEncoder(slaveEnc),
masterMotor(masterMtr),
slaveMotor(slaveMtr),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT)
{
   myPID.SetSampleTime(50);
   myPID.SetOutputLimits(-15, 15);
}

void MasterSlaveSpeedControl::enable(int initialMosh) {
    masterMotor->setPulseLength(initialMosh);
    slaveMotor->setPulseLength(initialMosh);
    Serial.println("enabling speedctl");
    enabled = true;
    myPID.SetMode(AUTOMATIC);
    myPID.SetTunings(kp, ki, kd);    
}

void MasterSlaveSpeedControl::disable() {
    Serial.println("disabling speedctl");
    myPID.SetMode(MANUAL);
    enabled = false;
    avgVelocity /= samples;
}

void MasterSlaveSpeedControl::normalPid() {
    double masterSpeed = masterEncoder->angularSpeed;
    double slaveSpeed  = slaveEncoder->angularSpeed;
    auto diff = slaveSpeed - masterSpeed;
    // input = diff;

    setpoint = masterSpeed;
    input = slaveSpeed;
    
    if (!myPID.Compute()) 
        return;    
            
    auto newSlave  =  slaveMotor->getPulseLength() + output;     
    if (newSlave > maxPwm)   newSlave = maxPwm;
    else if (newSlave < minPwm)   newSlave = minPwm;
    slaveMotor->setPulseLength((int) ceil(newSlave));     

    error += abs(diff);
    samples++;    
    
    Serial.print(" diff: ");
    Serial.print(diff);
    Serial.print(" output: ");
    Serial.print(output);
    Serial.print(" new slave: ");
    Serial.println(newSlave);    
}

void MasterSlaveSpeedControl::chafaPid() {
    double masterSpeed = masterEncoder->angularSpeed;
    double slaveSpeed  = slaveEncoder->angularSpeed;
    auto diff = masterSpeed - slaveSpeed;    

    auto newSlave = (double)slaveMotor->getPulseLength() + diff * 0.25; //0.5
    //newSlave -= 
    if (newSlave > maxPwm)   newSlave = maxPwm;
    else if (newSlave < minPwm)   newSlave = minPwm;

    slaveMotor->setPulseLength((int) ceil(newSlave));    

    Serial.print(" diff: ");
    Serial.print(diff);    
    Serial.print(" new slave: ");
    Serial.println(newSlave);    
}

void MasterSlaveSpeedControl::updatePID() {
    bool notReady = false;

    if (!enabled || notReady ) 
        return;

    
    //chafaPid();
    normalPid();
    
}
