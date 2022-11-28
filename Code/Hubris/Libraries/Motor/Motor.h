// include guard
#ifndef Motor_H
#define Motor_H

// include Arduino library
#include "Arduino.h"

class Motor
{
  public:
    Motor(int driverInputPin1, int driverInputPin2,int pwmPin, int standbyPin);
    void forward(int speed);
    void reverse(int speed);
    void stop();
    void brake();
    void freeWheel();
  private:
    int driverInputPin1;
    int driverInputPin2;
    int standbyPin;
    int pwmPin;
};

#endif