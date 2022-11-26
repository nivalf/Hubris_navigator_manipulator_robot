#include "Arduino.h"
#include "Ultrasonic.h"
#include "NewPing.h"

// Constructor
Ultrasonic::Ultrasonic(int trigPin, int echoPin)
{
    _echoPin = echoPin;
    _trigPin = trigPin;
    _maxDistance = 400;
}

void Ultrasonic::init()
{
    // do nothing
}

// get distance in cm
float Ultrasonic::getDistance()
{
    float distance;
    float duration;

    pinMode(_trigPin, OUTPUT);
    // Clears the trigPin
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    // This causes the sensor to send 8 ultrsonic bursts of 40 kHz
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // set the _echoPin as input. This is to enable using same pin for both input and output
    pinMode(_echoPin, INPUT);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(_echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2.0;

    return distance;
}