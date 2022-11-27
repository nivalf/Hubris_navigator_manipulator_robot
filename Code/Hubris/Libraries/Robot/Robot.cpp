#include "Arduino.h"
#include "Robot.h"

/*  Constructor
 *  @param  
        IRLeftpin
        IRRightpin
        MotorLeftDriverInputPin1
        MotorLeftDriverInputPin2
        MotorLeftPWMPin
        MotorLeftStandbyPin
        MotorRightDriverInputPin1
        MotorRightDriverInputPin2
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
Robot::Robot(int IRLeftPin, int IRRigthPin, int UltrasonicEchoPin, int UltrasonicTrigPin int MotorLeftPin1, int MotorLeftPin2, int MotorLeftStandbyPin, int MotorLeftPwmPin, int MotorRightPin1, int MotorRightPin2, int MotorRightStandbyPin, int MotorRightPwmPin) : IRLeft(IRLeftPin), IRRight(IRRigthPin), UltrasonicFront(UltrasonicEchoPin, UltrasonicTrigPin), MotorLeft(MotorLeftPin1, MotorLeftPin2, MotorLeftPwmPin, MotorLeftStandbyPin), MotorRight(MotorRightPin1, MotorRightPin2, MotorRightPwmPin, MotorRightStandbyPin)
{
}
