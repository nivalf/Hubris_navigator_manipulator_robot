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
    Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorLeftEncoderPin1, int MotorLeftEncoderPin2, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin, int MotorRightEncoderPin1, int MotorRightEncoderPin2);
    void init();
    void testIRSensors();
    void testSensors();
    void testMotors();
    void moveForward();
    void moveBackward();
    void steerLeft();
    void steerRight(); 
    void stop();
    void followLine();   
    int movetoBlackLine();
    Motor MotorLeft;
    Motor MotorRight;
    void getLeftWheelRotationCount();
    void getRightWheelRotationCount();

private:
    IR IRLeft;
    IR IRRight;
    Ultrasonic UltrasonicFront;
    int speed;
    int turnSpeed;
    float steeringFactor;
    int steeringCooloffTime;
};

#endif
