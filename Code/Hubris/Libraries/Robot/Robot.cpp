#include "Arduino.h"
#include "Robot.h"

/*  Constructor
 *  @param
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
Robot::Robot(int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin) : IRLeft(IRLeftPin), IRRight(IRRightPin), UltrasonicFront(UltrasonicEchoPin, UltrasonicTrigPin), MotorLeft(MotorLeftPin1, MotorLeftPin2, MotorLeftPwmPin, MotorLeftStandbyPin), MotorRight(MotorRightPin1, MotorRightPin2, MotorRightPwmPin, MotorRightStandbyPin)
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
    Serial.print(IRLeft.digitalRead()*300);
    Serial.print(" ");
    Serial.print("IR_Right(digital)*300:");
    Serial.print(IRRight.digitalRead()*300);
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