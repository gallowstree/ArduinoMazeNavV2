#include "AngularVelocityControl.h"
#include <Arduino.h>
#include <math.h>

AngularVelocityControl::AngularVelocityControl(EncoderReader* encoder, DcMotor* motor) :
encoder(encoder),
motor(motor),
myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT),
aTune(&input,&output),
error(0)
 {
    myPID.SetSampleTime(20);
    myPID.SetOutputLimits(-10, 10);
}

void AngularVelocityControl::enable(int initialMosh) {
    motor->setPulseLength(initialMosh);
    error = 0;
    samples = 0;
    Serial.print("enabling speedctl... initial mosh: ");
    Serial.println(initialMosh);
    enabled = true;
    myPID.SetMode(AUTOMATIC);

    if(tuning)
    {
      double outputStart=5;
      double aTuneStep=50, aTuneNoise=1, aTuneStartValue=16;
      unsigned int aTuneLookBack=20;
      output=aTuneStartValue;
      aTune.SetControlType(1);
      aTune.SetNoiseBand(aTuneNoise);
      aTune.SetOutputStep(aTuneStep);
      aTune.SetLookbackSec((int)aTuneLookBack);
      ATuneModeRemember = myPID.GetMode();
      tuning = true;
    }
    else
    { //cancel autotune
      aTune.Cancel();
      myPID.SetMode(ATuneModeRemember);
      myPID.SetTunings(kp, ki, kd);  
    }  
}

void AngularVelocityControl::disable() {
    Serial.println("disabling speedctl");
    myPID.SetMode(MANUAL);
    enabled = false;
    avgVelocity /= samples;
}

void AngularVelocityControl::updatePID() {    

    if (!enabled ) 
        return;
    
    input = encoder->angularSpeed;
    
    if(tuning)
    {
        byte val = (aTune.Runtime());
        //Serial.println("TUNING :D");
        if (val!=0)
        {
          tuning = false;
        }
        if(!tuning)
        { //we're done, set the tuning parameters
          kp = aTune.GetKp();
          ki = aTune.GetKi();
          kd = aTune.GetKd();
          Serial.println("Tuning done!");
          Serial.print("kp: ");
          Serial.print(kp);
          Serial.print("kd: ");
          Serial.print(kd);
          Serial.print("ki: ");
          Serial.print(ki);
          myPID.SetTunings(kp,ki,kd);
          myPID.SetMode(ATuneModeRemember);
        }
    }
    else
    {
        if (!myPID.Compute()) 
            return;    
            //Serial.print("input ");
            //Serial.println(motor->getPulseLength());
        auto newLeft = map(output, -10, 10, 0, 255);
        error += abs(setpoint - input);
        samples++;
        avgVelocity += input;

        if (newLeft > maxPwm) newLeft = maxPwm;
        else if (newLeft < minPwm) newLeft = minPwm;    
        
        motor->setPulseLength((int) ceil(newLeft));    
    }
}

