// include guard
#ifndef Robot_H
#define Robot_H

// include Arduino library
#include "Arduino.h"
#include "IR.h"
#include "Motor.h"
#include "Ultrasonic.h"

class Robot
{
public:
    Robot(int IRLeftPin, int IRRigthPin, int UltrasonicEchoPin, int UltrasonicTrigPin int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin);

private:
    IR IRLeft;
    IR IRRight;
    Motor MotorLeft;
    Motor MotorRight;
    Ultrasonic UltrasonicFront;
};

#endif
