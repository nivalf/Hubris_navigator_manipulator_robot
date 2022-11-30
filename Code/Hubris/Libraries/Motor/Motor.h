// include guard
#ifndef Motor_H
#define Motor_H

// include Arduino library
#include "Arduino.h"

class Motor
{
  public:
    Motor(int driverInputPin1, int driverInputPin2,int pwmPin, int standbyPin, int encoderPin1, int encoderPin2);
    void init();
    void forward(int speed);
    void reverse(int speed);
    void stop();
    void brake();
    void freeWheel();
    void countEncoderChannel1();
    void countEncoderChannel2();
    float getRotationCount();
  private:
    int driverInputPin1;
    int driverInputPin2;
    int standbyPin;
    int pwmPin;
    int encoderPin1;
    int encoderPin2;
    int encoderPin1PrevState;
    int encoderPin2PrevState;
    int encoderCount;
};

#endif
