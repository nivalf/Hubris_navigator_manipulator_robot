// include guard
#ifndef Ultrasonic_H
#define Ultrasonic_H

// include Arduino library
#include "Arduino.h"

#include "NewPing.h"

class Ultrasonic: public NewPing
{
  public:
    Ultrasonic(int echoPin, int trigPin);
    float getDistance();
  private:
    // pin number
    int _echoPin;
    int _trigPin;
};

#endif
