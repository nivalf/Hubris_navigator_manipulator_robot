#include "Robot.h"

// IR pins
#define IRLeftAPin A5
#define IRRightAPin A4
// BatteryVoltage
#define batteryVoltagePin A0
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

#define speed 150
#define reducedSpeed 50
#define lineFollowSpeed 50
#define turnSpeed 30

#define steeringFactor 0.2  // percentage
#define steeringCooloffTime 20

Robot Hubris(speed, turnSpeed, steeringFactor, steeringCooloffTime, IRLeftAPin, IRRightAPin, trigPin, echoPin, motorLeftPin1, motorLeftPin2, motorLeftStandbyPin, motorLeftPWMPin, motorLeftEncoderChannel_A_Pin, motorLeftEncoderChannel_B_Pin, motorRightPin2, motorRightPin1, motorRightStandbyPin, motorRightPWMPin, motorRightEncoderChannel_A_Pin, motorRightEncoderChannel_B_Pin, batteryVoltagePin);

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
  attachInterrupt(digitalPinToInterrupt(motorLeftEncoderChannel_A_Pin), motorLeftISR, RISING);
  attachInterrupt(digitalPinToInterrupt(motorRightEncoderChannel_A_Pin), motorRightISR, RISING);

  Hubris.init();
}

void loop(void) {
  timestamp = millis();

  Hubris.turnLeft();
  // Hubris.moveForward();
  // Hubris.getWheelStats();

  // Hubris.resetWheelEncoders();

  switch (Hubris.getState()) {
      //   case 0:  // calibration
      //     break;
    case 1:  // go forward
      Hubris.resetSpeed();
      Hubris.moveForward();
      Hubris.setState(2);
      break;
    case 2:  // reduce speed
      if (Hubris.blackLineInProximity()) {
        Hubris.setSpeed(reducedSpeed);
        Hubris.setState(3);
      }
      break;
    case 3:  // turn left
      if (Hubris.reachedBlackLine()) {
        Hubris.turnLeft();
        Hubris.setState(4);
        Hubris.setSpeed(lineFollowSpeed);
      }
      break;
    case 4:  // follow line
      Hubris.followLine();
      if (Hubris.buttonPressed()) {
        Hubris.setState(1);
      } else if (Hubris.reachedBlackLine()) {
        Hubris.setState(5);
      }
      break;
    case 5:
      Hubris.stop();
      break;
  }

  Serial.print("Runtime:");
  Serial.print(millis() - timestamp);
  Serial.println(' ');
}
