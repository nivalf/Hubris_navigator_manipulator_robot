#include "Arduino.h"
#include "RunningAvg.h"

// Constructor
RunningAvg::RunningAvg() : bufferIndex(0), windowSize(15)
{
    // initialize buffer
    for (int i = 0; i < windowSize; i++)
    {
        runningAverageBuffer[i] = 0.0;
    }
}

// Add the current value into buffer and get the average
float RunningAvg::getAvg(float currentVal)
{
    // Add the current value into buffer
    runningAverageBuffer[bufferIndex] = currentVal;
    bufferIndex = (bufferIndex + 1) % windowSize;

    float sum = 0;
    for (int i = 0; i < windowSize; i++)
    {
        sum += runningAverageBuffer[i];
    }

    // Serial.print("sum: ");
    // Serial.print(sum);
    // Serial.print(" bufferIndex: ");
    // Serial.print(bufferIndex);
    // Serial.print(" currentVal: ");
    // Serial.println(currentVal);

    return sum / windowSize;
}
