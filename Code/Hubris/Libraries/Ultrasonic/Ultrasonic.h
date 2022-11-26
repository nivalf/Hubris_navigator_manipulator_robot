// include guard
#ifndef Ultrasonic_H
#define Ultrasonic_H

// include Arduino library
#include "Arduino.h"

class Ultrasonic
{
  public:
    Ultrasonic(int echoPin, int trigPin);
    void init();
    float getDistance();
  private:
    // pin number
    int _echoPin;
    int _trigPin;
    int _maxDistance;
};

#endif
