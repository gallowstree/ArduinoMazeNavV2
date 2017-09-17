#ifndef MAZENAV_ANGULAR_SPEED_AT_H
#define MAZENAV_ANGULAR_SPEED_AT_H
#include "TwiddleAutotune.h"
#include "MasterSlaveSpeedControl.h"

class MasterSlaveAutotune : public TwiddleAutotune {
public:
    MasterSlaveAutotune(MasterSlaveSpeedControl* ctl);
    virtual double iterate(double p[]); 
    int initialMosh = 70;
    double targetVelocity = 0;
private:
    MasterSlaveSpeedControl* ctl;        
};

#endif