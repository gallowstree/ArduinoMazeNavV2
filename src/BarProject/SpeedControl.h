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
    volatile unsigned long time;

    EncoderReader* leftEncoder = nullptr;
    EncoderReader* rightEncoder = nullptr;

    DcMotor* leftMotor = nullptr;
    DcMotor* rightMotor = nullptr;

    double kp = 0;
    double ki = 0;
    double kd = 0;

    bool enabled = false;

    double minPwm = 60;
    double maxPwm = 130;

    double input = 0;
    double output = 0;
    double setpoint = 0;    

    double posX = 0;
    double posY = 0;
    double theta = 0;

    double error = 0;
    double refTheta = 0;
    double wheelsDistance = 0.088;
};

#endif