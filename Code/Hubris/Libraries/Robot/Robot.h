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
    Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorLeftEncoderChannelAPin, int MotorLeftEncoderChannelBPin, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin, int MotorRightEncoderChannelAPin, int MotorRightEncoderChannelBPin);
    void init();
    // test
    void testIRSensors();
    void testUltrasonicSensor();
    void testSensors();
    void testMotors();
    // state
    int getState();
    void setState(int state);
    // basic movement
    void moveForward();
    void moveBackward();
    void steerLeft();
    void steerRight(); 
    void stop();
    // advanced movement
    void followLine();   
    int movetoBlackLine();
    // motor & wheels
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
    int state;
};

#endif
