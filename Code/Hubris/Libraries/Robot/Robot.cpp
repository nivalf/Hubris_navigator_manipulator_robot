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
Robot::Robot(int speed, int turnSpeed, float steeringFactor, int steeringCooloffTime, int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int motorLeftPin1, int motorLeftPin2, int motorLeftStandbyPin, int motorLeftPwmPin, int motorLeftEncoderChannel_A_Pin, int motorLeftEncoderChannel_B_Pin, int motorRightPin1, int motorRightPin2, int motorRightStandbyPin, int motorRightPwmPin, int motorRightEncoderChannel_A_Pin, int motorRightEncoderChannel_B_Pin, int batteryVoltagePin) : // private variables
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      state(0),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      speed(speed),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      defaultSpeed(speed),
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

// 1.146067
// SPIN CIRCUMFERENCE
// const float CORRECTION_FACTOR = 1.13;
const float CORRECTION_FACTOR = 1.08;
const float WHEEL_CIRCUMFERENCE = 21.7; // in cm
const float ROTATION_FOR_QUARTER_SPIN_CIRCUMFERENCE = 0.717; // rotation of the wheel to move quarter of the circle

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

void Robot::setState(short int state)
{
    this->state = state;
}

int Robot::getState()
{
    return this->state;
}

// ***************** TESTS ***************** //

// Test the sensors & print the values
void Robot::logIRSensorValues()
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
void Robot::logUltraSonicSensorValues()
{
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
    logIRSensorValues();
    logUltraSonicSensorValues();
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

// ***************** SENSORS ***************** //
float Robot::getFrontDistance()
{
    logUltraSonicSensorValues();
    return UltrasonicFront.getDistanceExpAvg();
}

// ***************** SPEED ***************** //
// Set the speed of the robot
void Robot::setSpeed(short int speed)
{
    this->speed = speed;
}

// reset the speed to the default speed
void Robot::resetSpeed()
{
    this->speed = this->defaultSpeed;
}
// ***************** BASIC MOVEMENT ***************** //

// Move the robot forward
void Robot::moveForward()
{
    MotorLeft.forward((int)(CORRECTION_FACTOR * speed));
    MotorRight.forward(speed);
}

// Move the robot backward
void Robot::moveBackward()
{
    MotorLeft.reverse((int)(CORRECTION_FACTOR * speed));
    MotorRight.reverse(speed);
}

// Turn the robot left 90 degrees
void Robot::turnLeft()
{
    resetWheelEncoders();

    MotorLeft.reverse((int)(CORRECTION_FACTOR * turnSpeed));
    MotorRight.forward(turnSpeed);

    bool turning = true;

    while (turning)
    {   
        bool leftWheelTurned = abs(getLeftWheelRotationCount()) > ROTATION_FOR_QUARTER_SPIN_CIRCUMFERENCE;
        bool rightWheelTurned = abs(getRightWheelRotationCount()) > ROTATION_FOR_QUARTER_SPIN_CIRCUMFERENCE;
        
        // Stop left wheel once it has covered quarter wheel length
        if(leftWheelTurned){
            MotorLeft.brake();
        }
        // Stop right wheel once it has covered quarter wheel length
        if(rightWheelTurned){
            MotorRight.brake();
        }

        // Stop turning once both wheels have covered quarter wheel length
        if (leftWheelTurned && rightWheelTurned)
        {
            turning = false;
        }
    }

    resetWheelEncoders();
}

// Steer the robot left
void Robot::steerLeft()
{
    int reducedSpeed = speed * (1 - steeringFactor);

    MotorLeft.forward(reducedSpeed);
    MotorRight.forward(speed);
}

// Steer the robot right
void Robot::steerRight()
{
    int reducedSpeed = speed * (1 - steeringFactor);

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
    int leftIR = IRLeft.digitalRead();   // 0 for black, 1 for white
    int rightIR = IRRight.digitalRead(); // 0 for black, 1 for white

    testSensors();

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

    // if (rightIR == leftIR)
    // {
        moveForward();
    // }
}

// Ultrasonic value < 35
// Wheel rotation count < 60/WHEEL_CIRCUMFERENCE
bool Robot::blackLineInProximity()
{
    testSensors();
    return (UltrasonicFront.getDistance_RunningAvg() < 35) && (getLeftWheelRotationCount() < 60 / WHEEL_CIRCUMFERENCE);
}

// Reached the black line
bool Robot::reachedBlackLine()
{
    testSensors();
    int leftIR = IRLeft.digitalRead();
    int rightIR = IRRight.digitalRead();

    return (leftIR == 0 || rightIR == 0) ? 1 : 0;
}

// DEV NOTE: check with M
bool Robot::buttonPressed()
{
    // return (digitalRead(buttonPin) == 0) ? 1 : 0;
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

// Get the rotation count and angle of each wheels
void Robot::getWheelStats()
{
    Serial.print("Left Wheel>> Rotation Count: ");
    Serial.print(getLeftWheelRotationCount());
    Serial.print(" Angle: ");
    Serial.print(getLeftWheelAngle());
    Serial.print(" | Right Wheel>> Rotation Count: ");
    Serial.print(getRightWheelRotationCount());
    Serial.print(" Angle: ");
    Serial.println(getLeftWheelAngle());
}

float Robot::getLeftWheelRotationCount()
{
    return MotorLeft.getWheelRotationCount();
}

float Robot::getLeftWheelAngle()
{
    return MotorLeft.getWheelAngle();
}

/*
    Right wheel rotation is multiplied by -1 to
    make the visualise the rotation of both wheels
    positive when moving forward
*/
float Robot::getRightWheelRotationCount()
{
    return (-1.0) * MotorRight.getWheelRotationCount();
}

float Robot::getRightWheelAngle()
{
    return (-1.0) * MotorRight.getWheelAngle();
}

// Reset the encoder values of each motor
void Robot::resetWheelEncoders()
{
    MotorLeft.resetWheelEncoder();
    MotorRight.resetWheelEncoder();
}

// ***************** TRIALS ***************** //

void Robot::moveOneWheelLength()
{
    resetWheelEncoders();
    moveForward();

    bool moving = true;

    while (moving)
    {
        if(abs(getLeftWheelRotationCount()) >= 1.0){
            MotorLeft.brake();
        }
        if(abs(getRightWheelRotationCount()) >= 1.0){
            MotorRight.brake();
        }
    }
}