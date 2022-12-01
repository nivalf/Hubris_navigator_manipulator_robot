// include guard
#ifndef Motor_H
#define Motor_H

// include Arduino library
#include "Arduino.h"

class Motor
{
  public:
    Motor(int driverInputPin1, int driverInputPin2,int pwmPin, int standbyPin, int encoderPinChannel_A, int encoderPinChannel_B);
    void init();
    void forward(int speed);
    void reverse(int speed);
    void stop();
    void brake();
    void freeWheel();
    void countEncoderChannel_A();
    float getRotationCount();
  private:
    int driverInputPin1;
    int driverInputPin2;
    int standbyPin;
    int pwmPin;
    int encoderPinChannel_A;
    int encoderPinChannel_B;
    int channel_A_prevState;
    int channel_B_prevState;
    int encoderCount;
};

#endif
