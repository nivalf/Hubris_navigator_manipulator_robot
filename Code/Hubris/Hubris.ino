#include "Robot.h"

// IR pins
#define IRLeftAPin A5
#define IRRightAPin A4
// use same pin for trig & echo
#define trigPin 6
#define echoPin 6

// pins for left motor
#define motorLeftPin1 7
#define motorLeftPin2 8
#define motorLeftStandbyPin 9
#define motorLeftPWMPin 10
#define motorLeftEncoderChannel_A_Pin 2
#define motorLeftEncoderChannel_B_Pin 4
// pins for right motor
#define motorRightPin1 12
#define motorRightPin2 13
#define motorRightStandbyPin 9
#define motorRightPWMPin 11
#define motorRightEncoderChannel_A_Pin 3
#define motorRightEncoderChannel_B_Pin 5

#define speed 50
#define turnSpeed 250
#define steeringFactor 0.2  // percentage
#define steeringCooloffTime 20

Robot Hubris(speed, turnSpeed, steeringFactor, steeringCooloffTime, IRLeftAPin, IRRightAPin, trigPin, echoPin, motorLeftPin1, motorLeftPin2, motorLeftStandbyPin, motorLeftPWMPin, motorLeftEncoderChannel_A_Pin, motorLeftEncoderChannel_B_Pin, motorRightPin2, motorRightPin1, motorRightStandbyPin, motorRightPWMPin, motorRightEncoderChannel_A_Pin, motorRightEncoderChannel_B_Pin);

long timestamp;

// ISRs : Interrupt Service Routines
void motorLeftISR() {
  Hubris.countLeftEncoderChannel_A();
}

void motorRightISR() {
  Hubris.countRightEncoderChannel_A();
}

void setup(void) {
  Serial.begin(9600);  // We'll send debugging information via the Serial monitor

  // Attaching interrupt to pins for encoder
  attachInterrupt(digitalPinToInterrupt(motorLeftEncoderChannel_A_Pin), motorLeftISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motorRightEncoderChannel_A_Pin), motorRightISR, CHANGE);

  Hubris.init();
}

void loop(void) {
  timestamp = millis();

  switch (Hubris.getState()) {
    case 0:  // calibration
      break;
    case 1:  // go forward
      break;
    case 2:  // turn left
      break;
    case 3:  // follow line
      break;
    case 4:  // slow down
      break;
    case 5:  // move back
      break;
    case 6:  // turn left
      break;
    case 7:  // move forward
      break;
    case 8:  // turn left
      break;
    case 9:  // move forward
      break;
    case 10:  // stop
      break;
  }

  Serial.print("Runtime:");
  Serial.print(millis() - timestamp);
  Serial.println(' ');
}
