#ifndef MAZENAV_MASTER_SLAVE_SPEED_CTL_H
#define MAZENAV_MASTER_SLAVE_SPEED_CTL_H

#include "EncoderReader.h"
#include "DcMotor.h"
#include "PID_v1.h"

class MasterSlaveSpeedControl {
public:
    MasterSlaveSpeedControl(EncoderReader* masterEnc, EncoderReader* slaveEnc, DcMotor* masterMtr, DcMotor* slaveMtr);
    void enable(int initialMosh);
    void disable();
    void updatePID();

    double error = 0;
    double samples = 0; //Actually int
    double avgVelocity = 0;
    double setpoint = 0;      
    
    double kp = 4.5;
    double ki = 3;
    double kd = 0;
    
    EncoderReader* masterEncoder = nullptr;
    EncoderReader* slaveEncoder = nullptr;

    DcMotor* masterMotor = nullptr;
    DcMotor* slaveMotor = nullptr;
private:
    PID myPID;        

    bool enabled = false;

    double minPwm = 30;
    double maxPwm = 100;

    double oldError = 0;

    double input = 0;
    double output = 0;
    
    void normalPid();
    void chafaPid();
};

#endif