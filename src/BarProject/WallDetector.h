#ifndef MAZENAV_WALL_DETECTOR_H
#define MAZENAV_WALL_DETECTOR_H
#include "IRSensor.h"

//This could become an interface Correction
class WallDetector {

public:
    WallDetector(IRSensor* sensor);
    bool isFacingWall();

private:
    IRSensor* sensor;
};


#endif //MYARDUINOPROJECT_DISTANCESENSOR_H
