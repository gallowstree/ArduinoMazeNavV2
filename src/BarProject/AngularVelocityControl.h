#ifndef MAZENAV_ANGULAR_SPEED_CONTROL_H
#define MAZENAV_ANGULAR_SPEED_CONTROL_H

#include "EncoderReader.h"
#include "DcMotor.h"
#include "PID_v1.h"

class AngularVelocityControl {
public:
    AngularVelocityControl(EncoderReader* encoder, DcMotor* motor);
    void enable();
    void disable();
    void updatePID();
private:
    PID myPID;    
    EncoderReader* encoder = nullptr;
    DcMotor* motor = nullptr;    

    double kp = 3;
    double ki = 0;
    double kd = 0.25;

    bool enabled = false;

    double minPwm = 60;
    double maxPwm = 120;

    double input = 0;
    double output = 0;
    double setpoint = 14;    
};

#endif