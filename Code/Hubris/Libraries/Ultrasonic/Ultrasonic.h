// include guard
#ifndef Ultrasonic_H
#define Ultrasonic_H

// include Arduino library
#include "Arduino.h"

#include "NewPing.h"
#include "Filters.h"
#include "RunningAvg.h"

class Ultrasonic: public NewPing
{
  public:
    Ultrasonic(int echoPin, int trigPin);
    float getDistance();
    float getDistanceExpAvg();
    float getDistanceLowPassFiltered();
    float getDistance_RunningAvg();
  private:
    float filteredDistance;
    FilterOnePole lowPassFilter;
    RunningAvg distanceRunningAvg;
};

#endif
