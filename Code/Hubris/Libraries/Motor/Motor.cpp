#include "Motor.h"
#include "Arduino.h"
#include "Helpers.h"

/*
    FIT0450 Micro DC Motor with encoder
    https://wiki.dfrobot.com/Micro_DC_Motor_with_Encoder-SJ01_SKU__FIT0450

    Gear Ratio: 120:1
    Pulses per rotation of encoder disk: 8
    Pulses per rotation of motor shaft: 960
*/

// DEV NOTE: 
// Wheel rotates more than 1 when 960 is used.
// By trials, a value around 910 performs better.
const short int PULSES_PER_MOTOR_SHAFT_ROTATION = 960;

// Constructor
Motor::Motor(int driverInputPin1, int driverInputPin2, int pwmPin, int standbyPin, int encoderPinChannel_A, int encoderPinChannel_B) : // private variables initialization list
                                                                                                                                       driverInputPin1(driverInputPin1),
                                                                                                                                       driverInputPin2(driverInputPin2),
                                                                                                                                       standbyPin(standbyPin),
                                                                                                                                       pwmPin(pwmPin),
                                                                                                                                       encoderPinChannel_A(encoderPinChannel_A),
                                                                                                                                       encoderPinChannel_B(encoderPinChannel_B),
                                                                                                                                       channel_A_prevState(LOW),
                                                                                                                                       channel_B_prevState(LOW),
                                                                                                                                       encoderCount(0)
{
    pinMode(driverInputPin1, OUTPUT);
    pinMode(driverInputPin2, OUTPUT);
    pinMode(standbyPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    pinMode(encoderPinChannel_A, INPUT);
    pinMode(encoderPinChannel_B, INPUT);
}

void Motor::init()
{
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

// Count the number of pulses from the encoder of channel A
// This function is called by the interrupt service routine when
// the encoder channel A switches from low to high. (RISING EDGE)

/*
    Channel A   |   Channel B   |   Direction   |   Count
    ------------------------------------------------------
        0->1    |       0       |       CW      |   +1
        0->1    |       1       |       CCW     |   -1
        1->0    |       0       |       CCW     |   -1
        1->0    |       1       |       CW      |   +1
*/

// We only focus on the rising edge of channel A. Which is sufficient
// to count the number of pulses.
void Motor::countEncoderChannel_A()
{
    int channel_B_state = digitalRead(encoderPinChannel_B);
    channel_B_state == LOW ? encoderCount++ : encoderCount--;
}

float Motor::getWheelRotationCount()
{
    return (float)encoderCount / PULSES_PER_MOTOR_SHAFT_ROTATION;
}

float Motor::getWheelAngle()
{
    return getDecimal(getWheelRotationCount()) * 360.0;
}

// Reset the encoder value to 0
void Motor::resetWheelEncoder()
{
    encoderCount = 0;
}