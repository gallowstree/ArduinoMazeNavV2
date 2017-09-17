#include "WallDetector.h"

WallDetector::WallDetector(DistanceSensor* sensor) : 
sensor(sensor) {

}

bool WallDetector::isFacingWall() {
    return sensor->GetDistanceCm() < 13; //13 means there is a wall but we should have moved more in the forward direction
}