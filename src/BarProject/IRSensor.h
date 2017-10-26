#ifndef MAZENAV_IRSENSOR_H
#define MAZENAV_IRSENSOR_H

class IRSensor {

public:
    IRSensor(int inPin);
    bool ObstacleDetected();

private:
    const int inPin;
    
};

#endif