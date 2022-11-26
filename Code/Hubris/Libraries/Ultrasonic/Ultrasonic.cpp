#include "Arduino.h"
#include "Ultrasonic.h"
#include "NewPing.h"

// Constructor
Ultrasonic::Ultrasonic(int trigPin, int echoPin) : NewPing(trigPin, echoPin, 400)
{
    _echoPin = echoPin;
    _trigPin = trigPin;
}

// get distance in cm
float Ultrasonic::getDistance()
{
    float distance;
    float duration;

    // Calculating the distance
    distance = ping_cm();

    return distance;
}