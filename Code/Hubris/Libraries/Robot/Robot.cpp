#include "Arduino.h"
#include "Robot.h"
#include "Constants.h"

/*  Constructor
 *  @param
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
        -
        markerSwitchPin

 *  instantiates:
        IRLeft
        IRRight
        MotorLeft
        MotorRight
        UltrasonicFront
 */
Robot::Robot(int IRLeftPin, int IRRightPin, int UltrasonicTrigPin, int UltrasonicEchoPin, int motorLeftPin1, int motorLeftPin2, int motorLeftStandbyPin, int motorLeftPwmPin, int motorLeftEncoderChannel_A_Pin, int motorLeftEncoderChannel_B_Pin, int motorRightPin1, int motorRightPin2, int motorRightStandbyPin, int motorRightPwmPin, int motorRightEncoderChannel_A_Pin, int motorRightEncoderChannel_B_Pin, int batteryVoltagePin, int markerSwitchPin) : // private variables
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  markerSwitchPin(markerSwitchPin),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  // member classes
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  IRLeft(IRLeftPin),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  IRRight(IRRightPin),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  UltrasonicFront(UltrasonicEchoPin, UltrasonicTrigPin),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  MotorLeft(motorLeftPin1, motorLeftPin2, motorLeftPwmPin, motorLeftStandbyPin, motorLeftEncoderChannel_A_Pin, motorLeftEncoderChannel_B_Pin),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  MotorRight(motorRightPin1, motorRightPin2, motorRightPwmPin, motorRightStandbyPin, motorRightEncoderChannel_A_Pin, motorRightEncoderChannel_B_Pin),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  RobotBatteryVoltage(batteryVoltagePin)
{

    pinMode(markerSwitchPin, INPUT_PULLUP);
}

// Initialize the robot
void Robot::init()
{
    RobotBatteryVoltage.checkVoltage();

    setState(0);
    setSpeed(SPEED);
    setTurnSpeed(TURN_SPEED);

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

// ***************** SENSORS ***************** //
float Robot::getFrontDistance()
{
    // logUltraSonicSensorValues();
    // logWheelStats();
    return UltrasonicFront.getDistance();
}

bool Robot::isMarkerSwitchPressed()
{
    return !digitalRead(markerSwitchPin); // ! since pullup resistor is used
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
    this->speed = SPEED;
}

void Robot::setTurnSpeed(short int turnSpeed)
{
    this->turnSpeed = turnSpeed;
}

void Robot::resetTurnSpeed()
{
    this->turnSpeed = TURN_SPEED;
}
// ***************** BASIC MOVEMENT ***************** //

// Move the robot forward
void Robot::moveForward()
{
    // reOrient();
    MotorLeft.forward((int)(CORRECTION_FACTOR * speed));
    MotorRight.forward(speed);
}

// Move the robot backward
void Robot::moveBackward()
{
    MotorLeft.reverse((int)(CORRECTION_FACTOR * speed));
    MotorRight.reverse(speed);
}

// Steer the robot left
void Robot::steerLeft()
{
    moveForwardCurveLeft(speed * (1 + STEERING_FACTOR));
}

// Steer the robot right
void Robot::steerRight()
{
    moveForwardCurveRight(speed * (1 + STEERING_FACTOR));
}

// Stop the bot
void Robot::stop()
{
    MotorLeft.brake();
    MotorRight.brake();
}

// ***************** TURNING MOVEMENT ***************** //

// Turn the robot left 90 degrees
void Robot::turn90Left()
{
    // reOrient();
    resetWheelEncoders();

    MotorLeft.reverse((int)TURN_CORRECTION_FACTOR * turnSpeed);
    MotorRight.forward(turnSpeed);

    bool turning = true;

    while (turning)
    {
        bool leftWheelTurned = abs(getLeftWheelRotationCount()) > ROTATION_FOR_QUARTER_SPIN_CIRCUMFERENCE;
        bool rightWheelTurned = abs(getRightWheelRotationCount()) > ROTATION_FOR_QUARTER_SPIN_CIRCUMFERENCE;

        // Stop left wheel once it has covered quarter wheel length
        if (leftWheelTurned)
        {
            MotorLeft.brake();
        }
        // Stop right wheel once it has covered quarter wheel length
        if (rightWheelTurned)
        {
            MotorRight.brake();
        }

        // Stop turning once both wheels have covered quarter wheel length
        if (leftWheelTurned && rightWheelTurned)
        {
            turning = false;
        }
        // logWheelStats();
    }

    resetWheelEncoders();
}

// Turn the robot left 360 degrees
void Robot::turn360Left()
{
    short int count = 0;
    while (count < 4)
    {
        turn90Left();
        delay(500);
        count++;
    }
}

void Robot::orient90ccw()
{
    orient90(1);
}

void Robot::orient90cw()
{
    orient90(0);
}

// Orient the robot to 90 degrees relative to the starting position
// @params:
//      direction: 1 for front ccw, 0 for back cw
void Robot::orient90(short int direction)
{
    bool turning = true;

    while (turning)
    {
        setTurnSpeed(ORIENTATION_TURN_SPEED);
        direction ? moveForwardCurveLeft(3) : moveBackwardCurveRight(3);

        if (orientedAbove90())
        {
            turning = false;
        }
    }

    stop();
    resetTurnSpeed();
}

bool Robot::orientedAbove90()
{
    return getEncoderDifference() >= ENCODER_DIFF_FOR_90_DEGREE_ORIENTATION;
}

// ***************** CURVED MOVEMENT ***************** //
/*
    Functions to move the robot forward and backward with a curve
    @params:
        oppWheelSpeedFactor: ratio of the speed of the higher speed wheel to the lower speed wheel
        i.e., For a right curve, the left wheel will be moving at a higher speed than the right wheel
*/
void Robot::moveForwardCurveLeft(float oppWheelSpeedFactor)
{
    MotorLeft.forward(turnSpeed);
    MotorRight.forward(turnSpeed * oppWheelSpeedFactor);
}

void Robot::moveForwardCurveRight(float oppWheelSpeedFactor)
{
    MotorLeft.forward(turnSpeed * oppWheelSpeedFactor);
    MotorRight.forward(turnSpeed);
}

void Robot::moveBackwardCurveLeft(float oppWheelSpeedFactor)
{
    MotorLeft.reverse(turnSpeed);
    MotorRight.reverse(turnSpeed * oppWheelSpeedFactor);
}

void Robot::moveBackwardCurveRight(float oppWheelSpeedFactor)
{
    MotorLeft.reverse(turnSpeed * oppWheelSpeedFactor);
    MotorRight.reverse(turnSpeed);
}

// ***************** ADVANCED MOVEMENT ***************** //

// Line following
void Robot::followLine()
{
    int leftIR = IRLeft.digitalRead();   // 0 for black, 1 for white
    int rightIR = IRRight.digitalRead(); // 0 for black, 1 for white

    Serial.print("leftIR:");
    Serial.print(leftIR);
    Serial.print(" ");
    Serial.print("rightIR:");
    Serial.println(rightIR);

    if (leftIR < rightIR)
    {
        steerLeft();
    }
    else if (rightIR < leftIR)
    {
        steerRight();
    }
    else
    {
        moveForward();
    }
}

// Ultrasonic value < 35
bool Robot::blackLineInProximity()
{
    // testSensors();
    float dist = getFrontDistance();
    Serial.print("Dist:");
    Serial.println(dist);
    return (dist < 35.0);
}

// Reached the black line
bool Robot::reachedBlackLine()
{
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
void Robot::logWheelStats()
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

int Robot::getLeftWheelEncoderCount()
{
    return MotorLeft.getEncoderCount();
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

int Robot::getRightWheelEncoderCount()
{
    return (-1.0) * MotorRight.getEncoderCount();
}

float Robot::getRightWheelRotationCount()
{
    return (-1.0) * MotorRight.getWheelRotationCount();
}

float Robot::getRightWheelAngle()
{
    return (-1.0) * MotorRight.getWheelAngle();
}

// Difference in the encoder count of the two wheels
int Robot::getEncoderDifference()
{
    return abs(getLeftWheelEncoderCount() - getRightWheelEncoderCount());
}

// Reset the encoder values of each motor
void Robot::resetWheelEncoders()
{
    MotorLeft.resetWheelEncoder();
    MotorRight.resetWheelEncoder();
}

// Check if one wheel rotation is completed
bool Robot::completedOneWheelRotation()
{
    return completedWheelRotation(1.0);
}

// Check if specified rotation is completed
bool Robot::completedWheelRotation(float rotationCount)
{
    return (abs(getLeftWheelRotationCount()) >= rotationCount || abs(getRightWheelRotationCount()) >= rotationCount);
}

// ReOrient the robot to straight position. The bot gets tilted due to difference in the motors
void Robot::reOrient()
{
    stop();
    const float TOLERANCE = 0.01; // Allowed tolerance of difference b/w the two wheel rotations
    float diff = abs(getLeftWheelRotationCount() - getRightWheelRotationCount());
    Serial.println("Reorienting the bot... ");
    Serial.print("Difference in wheel rotations: ");
    Serial.print(diff);
    Serial.print(", Left Wheel Rotation: ");
    Serial.print(getLeftWheelRotationCount());
    Serial.print(", Right Wheel Rotation: ");
    Serial.println(getRightWheelRotationCount());

    while (diff > TOLERANCE)
    {
        // logWheelStats();
        if (getLeftWheelRotationCount() > getRightWheelRotationCount())
        {
            MotorLeft.brake();
            MotorRight.forward(turnSpeed);
        }
        else if (getLeftWheelRotationCount() < getRightWheelRotationCount())
        {
            MotorLeft.forward(turnSpeed);
            MotorRight.brake();
        }
        diff = abs(getLeftWheelRotationCount() - getRightWheelRotationCount());
    }
    stop();

    Serial.println("Orientation Complete... ");
    Serial.print("Difference in wheel rotations: ");
    Serial.print(diff);
    Serial.print(", Left Wheel Rotation: ");
    Serial.print(getLeftWheelRotationCount());
    Serial.print(", Right Wheel Rotation: ");
    Serial.println(getRightWheelRotationCount());
}

// ***************** TRIALS ***************** //

void Robot::moveOneWheelLength()
{
    resetWheelEncoders();
    moveForward();

    bool moving = true;

    while (moving)
    {
        if (abs(getLeftWheelRotationCount()) >= 1.0)
        {
            MotorLeft.brake();
        }
        if (abs(getRightWheelRotationCount()) >= 1.0)
        {
            MotorRight.brake();
        }
    }
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

// Print the encoder values of each wheel
void Robot::logEncoderValues()
{
    Serial.print("Left Wheel>> Encoder: ");
    Serial.print(MotorLeft.getEncoderCount());
    Serial.print(" | Right Wheel>> Encoder: ");
    Serial.println(MotorRight.getEncoderCount());
}

/*
    Due to the moment of inertia of the robot, the robot will not stop immediately
    after the motors are stopped. The robot will continue to move for a short while.

    This function is to test the drag of the robot at different speeds.
*/
void Robot::testDragAtDifferentSpeeds()
{
    int speeds[13] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 255};
    Serial.println("*********************************");
    Serial.println("Testing drag at different speeds. Copy the values to the spreadsheet.");
    Serial.println("*********************************");
    Serial.println("Speed, Stopped_wheel, Encoder_R, Encoder_L, Rotation_R, Rotation_L, Stopped_wheel, Encoder_R, Encoder_L, Rotation_R, Rotation_L, Encoder_R_Drag, Encoder_L_Drag, Rotation_R_Drag, Rotation_L_Drag");

    for (int i : speeds)
    {
        Serial.print(i);
        Serial.print(", ");

        bool leftMoving = true;
        bool rightMoving = true;

        resetWheelEncoders();

        // move forward
        MotorLeft.forward(i);
        MotorRight.forward(i);

        while (leftMoving || rightMoving)
        {
            if (getRightWheelRotationCount() >= 1.0 && rightMoving)
            {
                MotorRight.brake();
                rightMoving = false;

                Serial.print("Right,");
                Serial.print(getRightWheelEncoderCount());
                Serial.print(",");
                Serial.print(getLeftWheelEncoderCount());
                Serial.print(",");
                Serial.print(getRightWheelRotationCount());
                Serial.print(",");
                Serial.print(getLeftWheelRotationCount());
                Serial.print(",");
            }
            if (getLeftWheelRotationCount() >= 1.0 && leftMoving)
            {
                MotorLeft.brake();
                leftMoving = false;

                Serial.print("Left,");
                Serial.print(getRightWheelEncoderCount());
                Serial.print(",");
                Serial.print(getLeftWheelEncoderCount());
                Serial.print(",");
                Serial.print(getRightWheelRotationCount());
                Serial.print(",");
                Serial.print(getLeftWheelRotationCount());
                Serial.print(",");
            }
        }

        // both wheels stopped
        resetWheelEncoders();

        // Wait for 3 seconds for the drag to settle
        delay(3000);

        Serial.print(getRightWheelEncoderCount());
        Serial.print(",");
        Serial.print(getLeftWheelEncoderCount());
        Serial.print(",");
        Serial.print(getRightWheelRotationCount());
        Serial.print(",");
        Serial.println(getLeftWheelRotationCount());
    }

    // stop the loop on completion
    while (true)
    {
        // do nothing
    }
}

// Find the correction factor for the left wheel
void Robot::findMovingForwardCorrectionFactor()
{
    moveForward();
    Serial.println((float)getRightWheelEncoderCount() / getLeftWheelEncoderCount());
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