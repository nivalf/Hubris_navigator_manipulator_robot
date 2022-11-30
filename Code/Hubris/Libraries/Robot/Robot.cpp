#include "Arduino.h"
#include "Robot.h"

/*  Constructor
 *  @param
        speed: speed of the robot when moving forward or backward
        turnSpeed: speed of the robot when turning
        steeringFactor: the percentage difference between the speed of the left and right motors when turning
        steeringCooloffTime: the time in milliseconds that the robot will wait after turning before moving forward again

        IRLeftpin
        IRRightpin
        -
        MotorLeftPin1
        MotorLeftPin2
        MotorLeftPWMPin
        MotorLeftStandbyPin
        MotorLeftEncoderPin1
        MotorLeftEncoderPin2
        -
        MotorRightPin1
        MotorRightPin2
        MotorRightPWMPin
        MotorRightStandbyPin
        MotorRightEncoderPin1
        MotorRightEncoderPin2
        -
        UltrasonicEchoPin
        UltrasonicTrigPin

 *  instantiates:
        IRLeft
        IRRight
        MotorLeft
        MotorRight
        UltrasonicFront
 */
Robot::Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorLeftEncoderPin1, int MotorLeftEncoderPin2, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin, int MotorRightEncoderPin1, int MotorRightEncoderPin2) : 
// private variables
state(0),
speed(speed), 
turnSpeed(turnSpeed), 
steeringFactor(steeringFactor), 
steeringCooloffTime(steeringCooloffTime), 
// member classes
IRLeft(IRLeftPin), 
IRRight(IRRightPin), 
UltrasonicFront(UltrasonicEchoPin, UltrasonicTrigPin), 
MotorLeft(MotorLeftPin1, MotorLeftPin2, MotorLeftPwmPin, MotorLeftStandbyPin, MotorLeftEncoderPin1, MotorLeftEncoderPin2), 
MotorRight(MotorRightPin1, MotorRightPin2, MotorRightPwmPin, MotorRightStandbyPin, MotorRightEncoderPin1, MotorRightEncoderPin2)
{
}

// Initialize the robot
void Robot::init()
{
    IRLeft.init();
    IRRight.init();
    MotorLeft.init();
    MotorRight.init();
}


// Test the sensors & print the values
void Robot::testIRSensors()
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
    Serial.println(IRRight.digitalRead() * 300);
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


void Robot::setState(int state) {
    this->state = state;
}

int Robot::getState() {
    return this->state;
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

// Stop the bot
void Robot::stop()
{
    MotorLeft.brake();
    MotorRight.brake();
}

// Line following
void Robot::followLine()
{
    int leftIR = IRLeft.digitalRead();      // 0 for black, 1 for white
    int rightIR = IRRight.digitalRead();    // 0 for black, 1 for white

    if (leftIR < rightIR)
    {
        steerLeft();
        delay(steeringCooloffTime);
    }
    
    if (rightIR < leftIR)
    {
        steerRight();
        delay(steeringCooloffTime);
    }
    
    if (rightIR == leftIR)
    {
        moveForward();
    }
}

// Move to the blackLine
int Robot::movetoBlackLine()
{
    int leftIR = IRLeft.digitalRead();
    int rightIR = IRRight.digitalRead();

    if(leftIR == 0 || rightIR == 0)
    {
        return 1;
    }
    else
    {
        moveForward();
        return 0;
    }
}

void Robot::getLeftWheelRotationCount()
{
    Serial.print("Left wheel rotation: ");
    Serial.println(MotorLeft.getRotationCount());
}



void Robot::getRightWheelRotationCount()
{
    Serial.print("Right wheel rotation: ");
    Serial.println(MotorLeft.getRotationCount());
}