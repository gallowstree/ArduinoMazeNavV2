// #ifndef MAZENAV_ANGULAR_SPEED_CONTROL_H
// #define MAZENAV_ANGULAR_SPEED_CONTROL_H

// #include "EncoderReader.h"
// #include "DcMotor.h"
// #include "PID_v1.h"

// class AngularVelocityControl {
// public:
//     AngularVelocityControl(EncoderReader* encoder, DcMotor* motor);
//     void enable(int initialMosh);
//     void disable();
//     void updatePID();

//     double error = 0;
//     double samples = 0; //Actually int
//     double avgVelocity = 0;
//     double setpoint = 15;

//     EncoderReader* encoder = nullptr;
//     DcMotor* motor = nullptr; 
// private:
//     PID myPID;    
//     PID_ATune aTune;
//     bool tuning = false;
//     int ATuneModeRemember=2;
    
//     bool enabled = false;
//     double minPwm = 60;
//     double maxPwm = 120;
    

//     double input = 0;
//     double output = 0;        
// };

// #endif