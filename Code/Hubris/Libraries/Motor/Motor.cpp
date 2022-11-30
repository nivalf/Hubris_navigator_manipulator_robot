#include "Motor.h"
#include "Arduino.h"

// Constructor
Motor::Motor(int driverInputPin1, int driverInputPin2, int pwmPin, int standbyPin, int encoderPinChannel_A, int encoderPinChannel_B) : // private variables initialization list
                                                                                                                       driverInputPin1(driverInputPin1),
                                                                                                                       driverInputPin2(driverInputPin2),
                                                                                                                       standbyPin(standbyPin),
                                                                                                                       pwmPin(pwmPin),
                                                                                                                       encoderPinChannel_A(encoderPinChannel_A),
                                                                                                                       encoderPinChannel_B(encoderPinChannel_B),
                                                                                                                       encoderPinChannel_A_prevState(LOW),
                                                                                                                       encoderPinChannel_B_prevState(LOW),
                                                                                                                       encoderCount(0)
{
    pinMode(driverInputPin1, OUTPUT);
    pinMode(driverInputPin2, OUTPUT);
    pinMode(standbyPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    pinMode(encoderPinChannel_A, INPUT);
    pinMode(encoderPinChannel_B, INPUT);
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
void Motor::countEncoderChannel_A()
{
    int encoderPinChannel_A_state = digitalRead(encoderPinChannel_A);
    int encoderPinChannel_B_state = digitalRead(encoderPinChannel_B);

    int isRisingEdge = encoderPinChannel_A_state == HIGH && encoderPinChannel_A_prevState == LOW;
    int isFallingEdge = encoderPinChannel_A_state == LOW && encoderPinChannel_A_prevState == HIGH;

    /*
        Channel A   |   Channel B   |   Direction   |   Count
        ------------------------------------------------------
            0->1    |       0       |       CW      |   +1
            0->1    |       1       |       CCW     |   -1
            1->0    |       0       |       CCW     |   -1
            1->0    |       1       |       CW      |   +1
    */
    if (isRisingEdge)
        encoderPinChannel_B_state == LOW ? encoderCount++ : encoderCount--;
    else if (isFallingEdge)
        encoderPinChannel_B_state == HIGH ? encoderCount++ : encoderCount--;
    else
    { // Not supposed to enter here
        Serial.println("Error in counting encoder channel A");
        Serial.print("EncoderPinChannel_A_state: ");
        Serial.print(encoderPinChannel_A_state);
        Serial.print(", encoderPinChannel_B_state: ");
        Serial.print(encoderPinChannel_B_state);
        Serial.print(", encoderPinChannel_A_prevState: ");
        Serial.print(encoderPinChannel_A_prevState);
        Serial.print(", encoderPinChannel_B_prevState: ");
        Serial.println(encoderPinChannel_B_prevState);
    }

    encoderPinChannel_A_prevState = encoderPinChannel_A_state;
}

// Count the number of pulses from the encoder of channel B
void Motor::countEncoderChannel_B()
{
    int encoderPinChannel_A_state = digitalRead(encoderPinChannel_A);
    int encoderPinChannel_B_state = digitalRead(encoderPinChannel_B);

    int isRisingEdge = encoderPinChannel_B_state == HIGH && encoderPinChannel_B_prevState == LOW;
    int isFallingEdge = encoderPinChannel_B_state == LOW && encoderPinChannel_B_prevState == HIGH;

    /*
        Channel A   |   Channel B   |   Direction   |   Count
        ------------------------------------------------------
            1       |       0->1    |       CW      |   +1
            0       |       0->1    |       CCW     |   -1
            1       |       1->0    |       CCW     |   -1
            0       |       1->0    |       CW      |   +1
    */
    if (isRisingEdge)
        encoderPinChannel_A_state == HIGH ? encoderCount++ : encoderCount--;
    else if (isFallingEdge)
        encoderPinChannel_A_state == LOW ? encoderCount++ : encoderCount--;
    else
    { // Not supposed to enter here
        Serial.println("Error in counting encoder channel B");
        Serial.print("EncoderPinChannel_A_state: ");
        Serial.print(encoderPinChannel_A_state);
        Serial.print(", encoderPinChannel_B_state: ");
        Serial.print(encoderPinChannel_B_state);
        Serial.print(", encoderPinChannel_A_prevState: ");
        Serial.print(encoderPinChannel_A_prevState);
        Serial.print(", encoderPinChannel_B_prevState: ");
        Serial.println(encoderPinChannel_B_prevState);
    }

    encoderPinChannel_A_prevState = encoderPinChannel_A_state;
}

float Motor::getRotationCount() {
    return encoderCount/960.0;
}