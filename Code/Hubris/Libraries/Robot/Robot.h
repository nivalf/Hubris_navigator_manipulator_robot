// include guard
#ifndef Robot_H
#define Robot_H

// include Arduino library
#include "Arduino.h"
#include "IR.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "BatteryVoltage.h"

class Robot
{
public:
    Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int motorLeftPin1, int motorLeftPin2, int motorLeftStandbyPin, int motorLeftPwmPin, int motorLeftEncoderChannel_A_Pin, int motorLeftEncoderChannel_B_Pin, int motorRightPin1, int motorRightPin2, int motorRightStandbyPin, int motorRightPwmPin, int motorRightEncoderChannel_A_Pin, int motorRightEncoderChannel_B_Pin, int batteryVoltagePin);
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
    void countRightEncoderChannel_A();
    void getLeftWheelRotationCount();
    void getRightWheelRotationCount();

private:
    IR IRLeft;
    IR IRRight;
    Ultrasonic UltrasonicFront;
    Motor MotorLeft;
    Motor MotorRight;
    BatteryVoltage RobotBatteryVoltage; 
    int speed;
    int turnSpeed;
    float steeringFactor;
    int steeringCooloffTime;
    int state;
};

#endif
