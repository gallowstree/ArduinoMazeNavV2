#include "WallDetector.h"

WallDetector::WallDetector(IRSensor* sensor) : 
sensor(sensor) {

}

bool WallDetector::isFacingWall() {
    return sensor->ObstacleDetected();
}