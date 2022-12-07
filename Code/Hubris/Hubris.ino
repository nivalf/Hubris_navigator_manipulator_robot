#include "Robot.h"
#include "Constants.h"

// IR pins
#define IRLeftAPin A5
#define IRRightAPin A4

#define markerSwitchPin A3
// BatteryVoltage
#define batteryVoltagePin A0
// use same pin for trig & echo
#define trigPin 10  // 6
#define echoPin 10

// pins for left motor
#define motorLeftPin1 7
#define motorLeftPin2 8
#define motorLeftStandbyPin 9
#define motorLeftPWMPin 6 //10
#define motorLeftEncoderChannel_A_Pin 2
#define motorLeftEncoderChannel_B_Pin 4
// pins for right motor
#define motorRightPin1 12
#define motorRightPin2 13
#define motorRightStandbyPin 9
#define motorRightPWMPin 5 // 11
#define motorRightEncoderChannel_A_Pin 3
#define motorRightEncoderChannel_B_Pin 11 // 5

#define lineFollowSpeed 40

Robot Hubris(IRLeftAPin, IRRightAPin, trigPin, echoPin, motorLeftPin1, motorLeftPin2, motorLeftStandbyPin, motorLeftPWMPin, motorLeftEncoderChannel_A_Pin, motorLeftEncoderChannel_B_Pin, motorRightPin2, motorRightPin1, motorRightStandbyPin, motorRightPWMPin, motorRightEncoderChannel_A_Pin, motorRightEncoderChannel_B_Pin, batteryVoltagePin, markerSwitchPin);

long timestamp;
int count = 0;

// ISRs : Interrupt Service Routines
void motorLeftISR() {
  Hubris.countLeftEncoderChannel_A();
}

void motorRightISR() {
  Hubris.countRightEncoderChannel_A();
}

void setup(void) {
  Serial.begin(9600);  // We'll send debugging information via the Serial monitor

  //Attaching interrupt to pins for encoder
  attachInterrupt(digitalPinToInterrupt(motorLeftEncoderChannel_A_Pin), motorLeftISR, RISING);
  attachInterrupt(digitalPinToInterrupt(motorRightEncoderChannel_A_Pin), motorRightISR, RISING);

  Hubris.init();

  // DEV NOTE: Remove when not testing
  delay(1000);
}

void loop(void) {
  timestamp = millis();
  curve_path();
  
  // IR_US_operate();

  // Hubris.testSensors();

  // Hubris.findMovingForwardCorrectionFactor();

  // Serial.print("Runtime:");
  // Serial.print(millis() - timestamp);
  // Serial.println(' ');
  // Serial.print("Hubris State:");
  // Serial.println(Hubris.getState());
}
