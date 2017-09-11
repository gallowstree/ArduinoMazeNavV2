#ifndef MAZENAV_ANGULAR_SPEED_AT_H
#define MAZENAV_ANGULAR_SPEED_AT_H
#include "TwiddleAutotune.h"
#include "AngularVelocityControl.h"

class AngularVelocityAutotune : public TwiddleAutotune {
public:
    AngularVelocityAutotune(AngularVelocityControl* ctl);
    virtual double iterate(double p[]); 
    int initialMosh = 55;
    double targetVelocity = 15;
private:
    AngularVelocityControl* ctl;        
};

#endif