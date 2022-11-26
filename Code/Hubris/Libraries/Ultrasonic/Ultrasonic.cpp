#include "Arduino.h"
#include "Ultrasonic.h"
#include "NewPing.h"
#include "Filters.h"
#include "RunningAvg.h"

// Constructor
Ultrasonic::Ultrasonic(int trigPin, int echoPin) : NewPing(trigPin, echoPin, 400), lowPassFilter(LOWPASS, 100), distanceRunningAvg()
{
    filteredDistance = 0.0;
}

// get distance in cm
float Ultrasonic::getDistance()
{
    float duration;
    int iterations = 1;

    duration = ping_median(iterations);

    // Calculating the distance in cm from the duration of the ping & speed of sound
    float distance = ((duration / 2) * 0.0343);

    return distance;
}

/* Get the distance with an exponential average filter
    ref: https://www.megunolink.com/articles/coding/3-methods-filter-noisy-arduino-measurements/
*/
float Ultrasonic::getDistanceExpAvg()
{
    float alpha = 0.1; // smoothing factor

    float distance = getDistance();
    filteredDistance = alpha * distance + (1 - alpha) * (filteredDistance ? filteredDistance : distance);

    return filteredDistance;
}

/* Get the distance filtered using a LPF
    ref: https://github.com/JonHub/Filters
    ref: https://playground.arduino.cc/Code/Filters/
*/
float Ultrasonic::getDistanceLowPassFiltered()
{
    lowPassFilter.input(getDistance());

    return lowPassFilter.output();
}

float Ultrasonic::getDistance_RunningAvg()
{
    return distanceRunningAvg.getAvg(getDistance());
}