#ifndef MAZENAV_SPEED_DIFF_AT_H
#define MAZENAV_SPEED_DIFF_AT_H
#include "TwiddleAutotune.h"
#include "SpeedControl.h"

class SpeedDifferenceAutotune : public TwiddleAutotune {
public:
    SpeedDifferenceAutotune(SpeedControl* ctl);
    virtual double iterate(double p[]); 
    int initialMosh = 65;
    double targetDifference = 0;
private:
    SpeedControl* ctl;        
};

#endif