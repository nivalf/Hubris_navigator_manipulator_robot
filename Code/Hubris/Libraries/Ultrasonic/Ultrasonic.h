// include guard
#ifndef Ultrasonic_H
#define Ultrasonic_H

// include Arduino library
#include "Arduino.h"

#include "NewPing.h"
#include "RunningAvg.h"

class Ultrasonic: public NewPing
{
  public:
    Ultrasonic(int echoPin, int trigPin);
    float getDistance();
    float getDistanceExpAvg();
    float getDistance_RunningAvg();
  private:
    float filteredDistance;
    RunningAvg distanceRunningAvg;
};

#endif
