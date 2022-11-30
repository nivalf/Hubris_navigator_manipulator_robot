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
    Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int motorLeftPin1, int motorLeftPin2, int motorLeftStandbyPin, int MotorLeftPwmPin, int motorLeftEncoderChannel_A_Pin, int motorLeftEncoderChannel_B_Pin, int motorRightPin1, int motorRightPin2, int motorRightStandbyPin, int MotorRightPwmPin, int motorRightEncoderChannel_A_Pin, int motorRightEncoderChannel_B_Pin);
    void init();
    // test
    void testIRSensors();
    void testUltraSonicSensor();
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
    void countLeftEncoderChannel_A();
    void countLeftEncoderChannel_B();
    void countRightEncoderChannel_A();
    void countRightEncoderChannel_B();
    void getLeftWheelRotationCount();
    void getRightWheelRotationCount();

private:
    IR IRLeft;
    IR IRRight;
    Ultrasonic UltrasonicFront;
    Motor MotorLeft;
    Motor MotorRight;
    int speed;
    int turnSpeed;
    float steeringFactor;
    int steeringCooloffTime;
    int state;
};

#endif
