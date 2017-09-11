#ifndef MAZENAV_SPEED_CONTROL_H
#define MAZENAV_SPEED_CONTROL_H

#include "EncoderReader.h"
#include "DcMotor.h"
#include "PID_v1.h"
#include "PID_AutoTune_v0.h"

class SpeedControl {
public:
    SpeedControl(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor);
    void enable();
    void disable();
    void updatePID();
private:
    PID myPID;

    EncoderReader* leftEncoder = nullptr;
    EncoderReader* rightEncoder = nullptr;

    DcMotor* leftMotor = nullptr;
    DcMotor* rightMotor = nullptr;

    double kp = 9;
    double ki = 0;
    double kd = 0;

    bool enabled = false;

    double minPwm = 70;
    double maxPwm = 130;

    double input = 0;
    double output = 0;
    double setpoint = 0;    
};

#endif