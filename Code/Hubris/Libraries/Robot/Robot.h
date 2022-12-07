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
    Robot(int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int motorLeftPin1, int motorLeftPin2, int motorLeftStandbyPin, int motorLeftPwmPin, int motorLeftEncoderChannel_A_Pin, int motorLeftEncoderChannel_B_Pin, int motorRightPin1, int motorRightPin2, int motorRightStandbyPin, int motorRightPwmPin, int motorRightEncoderChannel_A_Pin, int motorRightEncoderChannel_B_Pin, int batteryVoltagePin, int markerSwitchPin);
    void init();
    // state
    int getState();
    void setState(short int state);
    // sensors
    float getFrontDistance();
    // speed
    void setSpeed(short int speed);
    void resetSpeed();
    // basic movement
    void moveForward();
    void moveBackward();
    void turn90Left();
    void turn360Left();
    void steerLeft();
    void steerRight(); 
    void stop();

    // curve movement
    void moveForwardCurveLeft(float wheelSpeedRatio);
    void moveForwardCurveRight(float wheelSpeedRatio);
    void moveBackwardCurveLeft(float wheelSpeedRatio);
    void moveBackwardCurveRight(float wheelSpeedRatio);

    // advanced movement
    void followLine();   
    bool reachedBlackLine();
    bool blackLineInProximity();
    bool buttonPressed();
    // motor & wheels
    void countLeftEncoderChannel_A();
    void countRightEncoderChannel_A();
    void logWheelStats();
    int getLeftWheelEncoderCount();
    int getRightWheelEncoderCount();
    float getLeftWheelRotationCount();
    float getRightWheelRotationCount();
    float getLeftWheelAngle();
    float getRightWheelAngle();
    void resetWheelEncoders();
    void reOrient();
    // trials
    void moveOneWheelLength();
    // test
    void logIRSensorValues();
    void logUltraSonicSensorValues();
    void testSensors();
    void testMotors();
    void logEncoderValues();
    void testDragAtDifferentSpeeds();
    void findMovingForwardCorrectionFactor();
    bool isMarkerSwitchPressed();

private:
    IR IRLeft;
    IR IRRight;
    Ultrasonic UltrasonicFront;
    Motor MotorLeft;
    Motor MotorRight;
    BatteryVoltage RobotBatteryVoltage; 
    int speed;
    int turnSpeed;
    short int state;
    short int markerSwitchPin;
};

#endif
