#include "Motor.h"
#include "Arduino.h"

// Constructor
Motor::Motor(int driverInputPin1, int driverInputPin2, int pwmPin, int standbyPin, int encoderPin1, int encoderPin2) : // private variables initialization list
                                                                                                                       driverInputPin1(driverInputPin1),
                                                                                                                       driverInputPin2(driverInputPin2),
                                                                                                                       standbyPin(standbyPin),
                                                                                                                       pwmPin(pwmPin),
                                                                                                                       encoderPin1(encoderPin1),
                                                                                                                       encoderPin2(encoderPin2),
                                                                                                                       encoderPin1PrevState(LOW),
                                                                                                                       encoderPin2PrevState(LOW),
                                                                                                                       encoderCount(0)
{
    pinMode(driverInputPin1, OUTPUT);
    pinMode(driverInputPin2, OUTPUT);
    pinMode(standbyPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
}

void Motor::init() {
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

// Count the number of pulses from the encoder of channel 1 (A)
void Motor::countEncoderChannel1()
{
    int encoderPin1State = digitalRead(encoderPin1);
    int encoderPin2State = digitalRead(encoderPin2);

    int isRisingEdge = encoderPin1State == HIGH && encoderPin1PrevState == LOW;
    int isFallingEdge = encoderPin1State == LOW && encoderPin1PrevState == HIGH;

    /*
        Pin 1   |   Pin 2   |   Direction   |   Count
        ------------------------------------------------
        0->1    |   0       |       CW      |   +1
        0->1    |   1       |       CCW     |   -1
        1->0    |   0       |       CCW     |   -1
        1->0    |   1       |       CW      |   +1
    */
    if (isRisingEdge)
        encoderPin2State == LOW ? encoderCount++ : encoderCount--;
    else if (isFallingEdge)
        encoderPin2State == HIGH ? encoderCount++ : encoderCount--;
    else
    { // Not supposed to enter here
        Serial.println("Error in counting encoder channel 1");
        Serial.print("EncoderPin1state: ");
        Serial.print(encoderPin1State);
        Serial.print(", EncoderPin2State: ");
        Serial.print(encoderPin2State);
        Serial.print(", EncoderPin1PrevState: ");
        Serial.print(encoderPin1PrevState);
        Serial.print(", EncoderPin2PrevState: ");
        Serial.println(encoderPin2PrevState);
    }

    encoderPin1PrevState = encoderPin1State;
}

// Count the number of pulses from the encoder of channel 2 (B)
void Motor::countEncoderChannel2()
{
    int encoderPin1State = digitalRead(encoderPin1);
    int encoderPin2State = digitalRead(encoderPin2);

    int isRisingEdge = encoderPin2State == HIGH && encoderPin2PrevState == LOW;
    int isFallingEdge = encoderPin2State == LOW && encoderPin2PrevState == HIGH;

    /*
        Pin 1   |   Pin 2   |   Direction   |   Count
        ------------------------------------------------
        1       |   0->1    |       CW      |   +1
        0       |   0->1    |       CCW     |   -1
        1       |   1->0    |       CCW     |   -1
        0       |   1->0    |       CW      |   +1
    */
    if (isRisingEdge)
        encoderPin1State == HIGH ? encoderCount++ : encoderCount--;
    else if (isFallingEdge)
        encoderPin1State == LOW ? encoderCount++ : encoderCount--;
    else
    { // Not supposed to enter here
        Serial.println("Error in counting encoder channel 2");
        Serial.print("EncoderPin1state: ");
        Serial.print(encoderPin1State);
        Serial.print(", EncoderPin2State: ");
        Serial.print(encoderPin2State);
        Serial.print(", EncoderPin1PrevState: ");
        Serial.print(encoderPin1PrevState);
        Serial.print(", EncoderPin2PrevState: ");
        Serial.println(encoderPin2PrevState);
    }

    encoderPin1PrevState = encoderPin1State;
}

float Motor::getRotationCount() {
    return encoderCount/960.0;
}