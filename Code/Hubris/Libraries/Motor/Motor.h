// include guard
#ifndef Motor_H
#define Motor_H

// include Arduino library
#include "Arduino.h"

class Motor
{
  public:
    Motor(int driverInputPin1, int driverInputPin2,int pwmPin, int standbyPin, int encoderPinChannelA, int encoderPinChannelB);
    void init();
    void forward(int speed);
    void reverse(int speed);
    void stop();
    void brake();
    void freeWheel();
    void countEncoderChannelA();
    void countEncoderChannelB();
    float getRotationCount();
  private:
    int driverInputPin1;
    int driverInputPin2;
    int standbyPin;
    int pwmPin;
    int encoderPinChannelA;
    int encoderPinChannelB;
    int encoderPinChannelAPrevState;
    int encoderPinChannelBPrevState;
    int encoderCount;
};

#endif
