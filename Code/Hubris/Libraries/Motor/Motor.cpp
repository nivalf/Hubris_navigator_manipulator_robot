#include "Motor.h"
#include "Arduino.h"

// Constructor
Motor::Motor(int driverInputPin1, int driverInputPin2,int pwmPin, int standbyPin ): _driverInputPin1(driverInputPin1), _driverInputPin2(driverInputPin2), _standbyPin(standbyPin), _pwmPin(pwmPin)
{
    pinMode(_driverInputPin1, OUTPUT);
    pinMode(_driverInputPin2, OUTPUT);
    pinMode(_standbyPin, OUTPUT);
    pinMode(_pwmPin, OUTPUT);
}

// Forward
void Motor::forward(int speed)
{
    digitalWrite(_driverInputPin1, HIGH);
    digitalWrite(_driverInputPin2, LOW);
    digitalWrite(_standbyPin, HIGH);
    analogWrite(_pwmPin, speed);
}

// Reverse the motor
void Motor::reverse(int speed)
{
    digitalWrite(_driverInputPin1, LOW);
    digitalWrite(_driverInputPin2, HIGH);
    digitalWrite(_standbyPin, HIGH);
    analogWrite(_pwmPin, speed);
}

// This function is used to stop the motor
void Motor::brake()
{
    digitalWrite(_driverInputPin1, HIGH);
    digitalWrite(_driverInputPin2, HIGH);
    digitalWrite(_standbyPin, HIGH);
    analogWrite(_pwmPin, 0);
}

// Stop motor by disabling standby pin
void Motor::stop()
{
    digitalWrite(_driverInputPin1, LOW);
    digitalWrite(_driverInputPin2, LOW);
    digitalWrite(_standbyPin, LOW);
    analogWrite(_pwmPin, 0);
}