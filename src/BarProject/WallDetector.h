#ifndef MAZENAV_WALL_DETECTOR_H
#define MAZENAV_WALL_DETECTOR_H
#include "DistanceSensor.h"

//This could become an interface Correction
class WallDetector {

public:
    WallDetector(DistanceSensor* sensor);
    bool isFacingWall();

private:
    DistanceSensor* sensor;
};


#endif //MYARDUINOPROJECT_DISTANCESENSOR_H
