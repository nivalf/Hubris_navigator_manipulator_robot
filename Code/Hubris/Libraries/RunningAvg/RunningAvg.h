// include guard
#ifndef RunningAvg_H
#define RunningAvg_H

// include Arduino library
#include "Arduino.h"

class RunningAvg
{
  public:
    RunningAvg();
    float getAvg(float);
  private:
    float runningAverageBuffer[15];
    int bufferIndex;
    int windowSize;
};

#endif
