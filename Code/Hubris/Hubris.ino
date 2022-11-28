#include "Robot.h"

// IR pins
#define IRLeftAPin A3
#define IRRightAPin A4
// use same pin for trig & echo
#define trigPin 6
#define echoPin 6
// pins for left motor
#define MotorLeftPin1 12
#define MotorLeftPin2 13
#define MotorLeftStandbyPin 9
#define MotorLeftPWMPin 11
// pins for right motor
#define MotorRightPin1 8
#define MotorRightPin2 7
#define MotorRightStandbyPin 9
#define MotorRightPWMPin 10

#define speed 150
#define turnSpeed 200
#define steeringFactor 0.8  // percentage

Robot Hubris(speed, turnSpeed, steeringFactor, IRLeftAPin, IRRightAPin, trigPin, echoPin, MotorLeftPin1, MotorLeftPin2, MotorLeftStandbyPin, MotorLeftPWMPin, MotorRightPin1, MotorRightPin2, MotorRightStandbyPin, MotorRightPWMPin);

long timestamp;

void setup(void) {
  Serial.begin(9600);  // We'll send debugging information via the Serial monitor

  Hubris.init();
}

void loop(void) {
  timestamp = millis();

  Hubris.steerLeft();
  delay(2000);
  Hubris.steerRight();
  delay(2000);

  Serial.print("Runtime:");
  Serial.print(millis() - timestamp);
  Serial.println(' ');

  // delay(100);
}
