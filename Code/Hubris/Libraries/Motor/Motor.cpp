#include "Motor.h"
#include "Arduino.h"

// Constructor
Motor::Motor(int driverInputPin1, int driverInputPin2,int pwmPin, int standbyPin ): driverInputPin1(driverInputPin1), driverInputPin2(driverInputPin2), standbyPin(standbyPin), pwmPin(pwmPin)
{
    pinMode(driverInputPin1, OUTPUT);
    pinMode(driverInputPin2, OUTPUT);
    pinMode(standbyPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
}

// Forward
void Motor::forward(int speed)
{
    digitalWrite(driverInputPin1, HIGH);
    digitalWrite(driverInputPin2, LOW);
    digitalWrite(standbyPin, HIGH);
    analogWrite(pwmPin, speed);
}

// Reverse the motor
void Motor::reverse(int speed)
{
    digitalWrite(driverInputPin1, LOW);
    digitalWrite(driverInputPin2, HIGH);
    digitalWrite(standbyPin, HIGH);
    analogWrite(pwmPin, speed);
}

// This function is used to stop the motor
void Motor::brake()
{
    digitalWrite(driverInputPin1, HIGH);
    digitalWrite(driverInputPin2, HIGH);
    digitalWrite(standbyPin, HIGH);
    analogWrite(pwmPin, 0);
}

// Stop motor by disabling standby pin
void Motor::stop()
{
    digitalWrite(driverInputPin1, LOW);
    digitalWrite(driverInputPin2, LOW);
    digitalWrite(standbyPin, LOW);
    analogWrite(pwmPin, 0);
}

