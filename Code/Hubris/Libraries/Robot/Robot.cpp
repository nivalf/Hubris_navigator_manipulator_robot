#include "Arduino.h"
#include "Robot.h"

/*  Constructor
 *  @param
        speed: speed of the robot when moving forward or backward
        turnSpeed: speed of the robot when turning
        steeringFactor: the percentage difference between the speed of the left and right motors when turning

        IRLeftpin
        IRRightpin
        MotorLeftPin1
        MotorLeftPin2
        MotorLeftPWMPin
        MotorLeftStandbyPin
        MotorRightPin1
        MotorRightPin2
        MotorRightPWMPin
        MotorRightStandbyPin
        UltrasonicEchoPin
        UltrasonicTrigPin

 *  instantiates:
        IRLeft
        IRRight
        MotorLeft
        MotorRight
        UltrasonicFront
 */
Robot::Robot(int speed, int turnSpeed, float steeringFactor, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin) : speed(speed), turnSpeed(turnSpeed), steeringFactor(steeringFactor), IRLeft(IRLeftPin), IRRight(IRRightPin), UltrasonicFront(UltrasonicEchoPin, UltrasonicTrigPin), MotorLeft(MotorLeftPin1, MotorLeftPin2, MotorLeftPwmPin, MotorLeftStandbyPin), MotorRight(MotorRightPin1, MotorRightPin2, MotorRightPwmPin, MotorRightStandbyPin)
{
}

// Initialize the robot
void Robot::init()
{
    IRLeft.init();
    IRRight.init();
}

// Test the sensors & print the values
void Robot::testSensors()
{
    Serial.print("IR_Left:");
    Serial.print(IRLeft.read());
    Serial.print(" ");
    Serial.print("IR_Right:");
    Serial.print(IRRight.read());
    Serial.print(" ");
    Serial.print("IR_Left(digital)*300:");
    Serial.print(IRLeft.digitalRead() * 300);
    Serial.print(" ");
    Serial.print("IR_Right(digital)*300:");
    Serial.print(IRRight.digitalRead() * 300);
    Serial.print(" ");
    Serial.print("Dist:");
    Serial.print(UltrasonicFront.getDistance());
    Serial.print(" ");
    Serial.print("Dist(exp_avg):");
    Serial.print(UltrasonicFront.getDistanceExpAvg());
    Serial.print(" ");
    Serial.print("Dist(running_avg):");
    Serial.println(UltrasonicFront.getDistance_RunningAvg());
}

// Test the motors
void Robot::testMotors()
{
    MotorLeft.forward(255);
    MotorRight.forward(255);
    delay(1000);
    MotorLeft.brake();
    MotorRight.brake();
    delay(1000);
    MotorLeft.reverse(255);
    MotorRight.reverse(255);
    delay(1000);
    MotorLeft.brake();
    MotorRight.brake();
    delay(1000);
    MotorLeft.forward(255);
    MotorRight.reverse(255);
    delay(1000);
    MotorLeft.brake();
    MotorRight.brake();
    delay(1000);
    MotorLeft.reverse(255);
    MotorRight.forward(255);
    delay(1000);
    MotorLeft.brake();
    MotorRight.brake();
    delay(1000);
}

// Move the robot forward
void Robot::moveForward()
{
    MotorLeft.forward(speed);
    MotorRight.forward(speed);
}

// Move the robot backward
void Robot::moveBackward()
{
    MotorLeft.reverse(speed);
    MotorRight.reverse(speed);
}

// Steer the robot left
void Robot::steerLeft()
{
    int reducedSpeed = speed * (1-steeringFactor);

    MotorLeft.forward(reducedSpeed);
    MotorRight.forward(speed);
}

// Steer the robot right
void Robot::steerRight()
{
    int reducedSpeed = speed * (1-steeringFactor);
    
    MotorLeft.forward(speed);
    MotorRight.forward(reducedSpeed);
}