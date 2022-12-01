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
        motorLeftPin1
        motorLeftPin2
        motorLeftPWMPin
        motorLeftStandbyPin
        motorLeftEncoderChannel_A_Pin
        motorLeftEncoderChannel_B_Pin
        -
        motorRightPin1
        motorRightPin2
        motorRightPWMPin
        motorRightStandbyPin
        motorRightEncoderChannel_A_Pin
        motorRightEncoderChannel_B_Pin
        -
        UltrasonicEchoPin
        UltrasonicTrigPin
        -
        batteryVoltagePin

 *  instantiates:
        IRLeft
        IRRight
        MotorLeft
        MotorRight
        UltrasonicFront
 */
Robot::Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int motorLeftPin1, int motorLeftPin2, int motorLeftStandbyPin, int motorLeftPwmPin, int motorLeftEncoderChannel_A_Pin, int motorLeftEncoderChannel_B_Pin, int motorRightPin1, int motorRightPin2, int motorRightStandbyPin, int motorRightPwmPin, int motorRightEncoderChannel_A_Pin, int motorRightEncoderChannel_B_Pin, int batteryVoltagePin) : 
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
MotorLeft(motorLeftPin1, motorLeftPin2, motorLeftPwmPin, motorLeftStandbyPin, motorLeftEncoderChannel_A_Pin, motorLeftEncoderChannel_B_Pin), 
MotorRight(motorRightPin1, motorRightPin2, motorRightPwmPin, motorRightStandbyPin, motorRightEncoderChannel_A_Pin, motorRightEncoderChannel_B_Pin),
RobotBatteryVoltage(batteryVoltagePin)
{
}

// Initialize the robot
void Robot::init()
{
    RobotBatteryVoltage.checkVoltage();
    IRLeft.init();
    IRRight.init();
    MotorLeft.init();
    MotorRight.init();
}

// ***************** STATE ***************** //

void Robot::setState(int state) {
    this->state = state;
}

int Robot::getState() {
    return this->state;
}

// ***************** TESTS ***************** //

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

// Test ultrasonic sensor & print the values
void Robot::testUltraSonicSensor(){
    Serial.print("Dist:");
    Serial.print(UltrasonicFront.getDistance());
    Serial.print(" ");
    Serial.print("Dist(exp_avg):");
    Serial.print(UltrasonicFront.getDistanceExpAvg());
    Serial.print(" ");
    Serial.print("Dist(running_avg):");
    Serial.println(UltrasonicFront.getDistance_RunningAvg());
}

// Test the sensors & print the values
void Robot::testSensors()
{
    testIRSensors();
    testUltraSonicSensor();
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

// ***************** BASIC MOVEMENT ***************** //

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

// ***************** ADVANCED MOVEMENT ***************** //

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

// ***************** WHEELS ***************** //

/* Encoder methods of each wheels are defines as below 
to be used in the interrupt functions in the setup() on the 
main .ino file*/

// Left wheel
void Robot::countLeftEncoderChannel_A()
{
    MotorLeft.countEncoderChannel_A();
}

// Right wheel
void Robot::countRightEncoderChannel_A()
{
    MotorRight.countEncoderChannel_A();
}

// Rotation count of the wheels
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