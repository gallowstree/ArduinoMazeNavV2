#include "WallDetector.h"
#include "Arduino.h"

WallDetector::WallDetector(DistanceSensor* sensor) : 
sensor(sensor) {

}

bool WallDetector::isFacingWall() {
    float cm = 0;
    
    do {
        cm = sensor->GetDistanceCm();
    } while (cm < 1);
    // cm = sensor->GetDistanceCm();
    Serial.print("Read: ");
    Serial.println(cm );
    return cm < 13; //13 means there is a wall but we should have moved more in the forward direction
}