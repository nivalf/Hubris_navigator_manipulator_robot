#include "Robot.h"

// IR pins
#define IRLeftAPin A5
#define IRRightAPin A4
// use same pin for trig & echo
#define trigPin 6
#define echoPin 6



// pins for left motor
#define MotorLeftPin1 7
#define MotorLeftPin2 8
#define MotorLeftStandbyPin 9
#define MotorLeftPWMPin 10
#define MotorLeftEncoder1 3
#define MotorLeftEncoder2 5
// pins for right motor
#define MotorRightPin1 12
#define MotorRightPin2 13
#define MotorRightStandbyPin 9
#define MotorRightPWMPin 11
#define MotorRightEncoder1 2
#define MotorRightEncoder2 4

#define speed 50
#define turnSpeed 250
#define steeringFactor 0.2  // percentage
#define steeringCooloffTime 20

Robot Hubris(speed, turnSpeed, steeringFactor, steeringCooloffTime, IRLeftAPin, IRRightAPin, trigPin, echoPin, MotorLeftPin1, MotorLeftPin2, MotorLeftStandbyPin, MotorLeftPWMPin, MotorRightPin2, MotorRightPin1, MotorRightStandbyPin, MotorRightPWMPin);

long timestamp;
int blackCount = 0;

void setup(void) {
  Serial.begin(9600);  // We'll send debugging information via the Serial monitor

  Hubris.init();
}

void loop(void) {
  timestamp = millis();

  // while(!blackCount) {
  //   blackCount = Hubris.movetoBlackLine();
  // }
  // Hubris.stop();

  Hubris.testIRSensors();
  Hubris.followLine();


  Serial.print("Runtime:");
  Serial.print(millis() - timestamp);
  Serial.println(' ');
}
