#ifndef MAZENAV_DC_MOTOR_H
#define MAZENAV_DC_MOTOR_H

enum Direction { FORWARD, BACKWARDS };

class DcMotor {

public: // Maybe these public methods should be an interface to abstract other types of motor and decouple from arduino...    

    DcMotor(int out1, int out2, int pwmPin, int initialPulseLength, double kp, double kd, double ki);
    
    void move(Direction direction);

    void stop();    

    void setPulseLength(int p);

    int getPulseLength();

    double kp;
    double kd;
    double ki;
        
private:
    // PWM output power [0 – 255]
    int pulseLength;

    // H-Bridge's 'enable' pin for this motor, will be PWM'ed to adjust speed
    const int pwmPin;

    //H–Bridge outputs
    const int out1;
    const int out2;    
};

#endif