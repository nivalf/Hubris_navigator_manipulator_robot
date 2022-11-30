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
#define MotorLeftEncoderPin1 2
#define MotorLeftEncoderPin2 4
// pins for right motor
#define MotorRightPin1 12
#define MotorRightPin2 13
#define MotorRightStandbyPin 9
#define MotorRightPWMPin 11
#define MotorRightEncoderPin1 3
#define MotorRightEncoderPin2 5

#define speed 50
#define turnSpeed 250
#define steeringFactor 0.2  // percentage
#define steeringCooloffTime 20

Robot Hubris(speed, turnSpeed, steeringFactor, steeringCooloffTime, IRLeftAPin, IRRightAPin, trigPin, echoPin, MotorLeftPin1, MotorLeftPin2, MotorLeftStandbyPin, MotorLeftPWMPin, MotorLeftEncoderPin1, MotorLeftEncoderPin2, MotorRightPin2, MotorRightPin1, MotorRightStandbyPin, MotorRightPWMPin, MotorRightEncoderPin1, MotorRightEncoderPin2);

long timestamp;
int blackCount = 0;


void motorLeftISR() {
  Hubris.MotorLeft.countEncoderChannel1();
}

void motorRightISR() {
  Hubris.MotorRight.countEncoderChannel1();
}

void setup(void) {
  Serial.begin(9600);  // We'll send debugging information via the Serial monitor


  // Attaching interrupt to pins for encoder
  attachInterrupt(digitalPinToInterrupt(MotorLeftEncoderPin1), motorLeftISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorRightEncoderPin1), motorRightISR, CHANGE);

  Hubris.init();
}

void loop(void) {
  timestamp = millis();

  switch(Hubris.getState()){
    case 0:   // calibration
      break;
    case 1:   // go forward
      break;
    case 2:   // turn left
      break;
    case 3:   // follow line
      break;
    case 4:   // slow down
      break;
    case 5:   // move back
      break;
    case 6:   // turn left
      break;
    case 7:   // move forward
      break;  
    case 8:   // turn left
      break;
    case 9:   // move forward
      break;
    case 10:  // stop
      break;
  }

  Serial.print("Runtime:");
  Serial.print(millis() - timestamp);
  Serial.println(' ');

  delay(100);
}
