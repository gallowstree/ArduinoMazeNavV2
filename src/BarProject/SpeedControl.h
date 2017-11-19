#ifndef MAZENAV_SPEED_CONTROL_H
#define MAZENAV_SPEED_CONTROL_H

#include "EncoderReader.h"
#include "DcMotor.h"
#include "PID_v1.h"
#include "PID_AutoTune_v0.h"

class SpeedControl {
public:
    SpeedControl(EncoderReader* leftEncoder, EncoderReader* rightEncoder, DcMotor* leftMotor, DcMotor* rightMotor);
    void enable(double currentTheta);
    void disable();
    void updatePID(bool adjustPWM);
    double posX = 0;
    double posY = 0;
    double theta = 0;
    double kp = 20.0;
    double ki = 2;
    double kd = 5;
private:
    volatile unsigned long time;

    EncoderReader* leftEncoder = nullptr;
    EncoderReader* rightEncoder = nullptr;

    DcMotor* leftMotor = nullptr;
    DcMotor* rightMotor = nullptr;

    


    bool enabled = false;

    double minPwm = 50;
    double maxPwm = 130;

    double input = 0;
    double output = 0;
    double setpoint = 0;    


    double error = 0;
    double integral = 0;
    double differential = 0;
    double lastError = 0;
    double refTheta = 0;
    double wheelsDistance = 0.078;
};

#endif