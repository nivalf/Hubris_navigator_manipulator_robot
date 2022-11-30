#include "Motor.h"
#include "Arduino.h"

// Constructor
Motor::Motor(int driverInputPin1, int driverInputPin2, int pwmPin, int standbyPin, int encoderPinChannelA, int encoderPinChannelB) : // private variables initialization list
                                                                                                                       driverInputPin1(driverInputPin1),
                                                                                                                       driverInputPin2(driverInputPin2),
                                                                                                                       standbyPin(standbyPin),
                                                                                                                       pwmPin(pwmPin),
                                                                                                                       encoderPinChannelA(encoderPinChannelA),
                                                                                                                       encoderPinChannelB(encoderPinChannelB),
                                                                                                                       encoderPinChannelAPrevState(LOW),
                                                                                                                       encoderPinChannelBPrevState(LOW),
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

// Count the number of pulses from the encoder of channel A
void Motor::countEncoderChannelA()
{
    int encoderPinChannelAState = digitalRead(encoderPinChannelA);
    int encoderPinChannelBState = digitalRead(encoderPinChannelB);

    int isRisingEdge = encoderPinChannelAState == HIGH && encoderPinChannelAPrevState == LOW;
    int isFallingEdge = encoderPinChannelAState == LOW && encoderPinChannelAPrevState == HIGH;

    /*
        Channel A   |   Channel B   |   Direction   |   Count
        ------------------------------------------------------
            0->1    |       0       |       CW      |   +1
            0->1    |       1       |       CCW     |   -1
            1->0    |       0       |       CCW     |   -1
            1->0    |       1       |       CW      |   +1
    */
    if (isRisingEdge)
        encoderPinChannelBState == LOW ? encoderCount++ : encoderCount--;
    else if (isFallingEdge)
        encoderPinChannelBState == HIGH ? encoderCount++ : encoderCount--;
    else
    { // Not supposed to enter here
        Serial.println("Error in counting encoder channel A");
        Serial.print("EncoderPinChannelAState: ");
        Serial.print(encoderPinChannelAState);
        Serial.print(", EncoderPin2State: ");
        Serial.print(encoderPinChannelBState);
        Serial.print(", EncoderPin1PrevState: ");
        Serial.print(encoderPinChannelAPrevState);
        Serial.print(", EncoderPin2PrevState: ");
        Serial.println(encoderPinChannelBPrevState);
    }

    encoderPinChannelAPrevState = encoderPinChannelAState;
}

// Count the number of pulses from the encoder of channel B
void Motor::countEncoderChannelB()
{
    int encoderPinChannelAState = digitalRead(encoderPinChannelA);
    int encoderPinChannelBState = digitalRead(encoderPinChannelB);

    int isRisingEdge = encoderPinChannelBState == HIGH && encoderPinChannelBPrevState == LOW;
    int isFallingEdge = encoderPinChannelBState == LOW && encoderPinChannelBPrevState == HIGH;

    /*
        Channel A   |   Channel B   |   Direction   |   Count
        ------------------------------------------------------
            1       |       0->1    |       CW      |   +1
            0       |       0->1    |       CCW     |   -1
            1       |       1->0    |       CCW     |   -1
            0       |       1->0    |       CW      |   +1
    */
    if (isRisingEdge)
        encoderPinChannelAState == HIGH ? encoderCount++ : encoderCount--;
    else if (isFallingEdge)
        encoderPinChannelAState == LOW ? encoderCount++ : encoderCount--;
    else
    { // Not supposed to enter here
        Serial.println("Error in counting encoder channel B");
        Serial.print("EncoderPinChannelAState: ");
        Serial.print(encoderPinChannelAState);
        Serial.print(", EncoderPin2State: ");
        Serial.print(encoderPinChannelBState);
        Serial.print(", EncoderPin1PrevState: ");
        Serial.print(encoderPinChannelAPrevState);
        Serial.print(", EncoderPin2PrevState: ");
        Serial.println(encoderPinChannelBPrevState);
    }

    encoderPinChannelAPrevState = encoderPinChannelAState;
}

float Motor::getRotationCount() {
    return encoderCount/960.0;
}