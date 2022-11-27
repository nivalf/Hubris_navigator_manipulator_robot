#include "IR.h"
#include "Ultrasonic.h"
#include "Motor.h"

#define IRLeftAPin A4
#define IRRightAPin A5

// use same pin for trig & echo
#define trigPin 9
#define echoPin 9

// pins for motor
#define driverInputPin1 4
#define driverInputPin2 5
#define standbyPin 2
#define pwmPin 3

float IR1Reading;      // the analog reading from the IR sensor
float IR2Reading;      // the analog reading from the IR sensor

long timestamp;

// digital readings
bool IR1DigitalReading;
bool IR2DigitalReading;

// distance reading
float distance;
float distance_expAvg;
float distance_ra;

IR IRLeft(IRLeftAPin);
IR IRRight(IRRightAPin);

Ultrasonic Sonar(trigPin, echoPin);

Motor RightMotor(driverInputPin1, driverInputPin2, standbyPin, pwmPin);
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor

  IRLeft.init();
  IRRight.init();
}
 
void loop(void) {
  timestamp = millis();

  IR1Reading = IRLeft.read();
  IR2Reading = IRRight.read();

  IR1DigitalReading = IRLeft.digitalRead();
  IR2DigitalReading = IRRight.digitalRead();

  distance = Sonar.getDistance();
  delay(1);
  distance_expAvg = Sonar.getDistanceExpAvg();
  delay(1);
  distance_ra = Sonar.getDistance_RunningAvg();
  delay(1);

  RightMotor.reverse(50);
  delay(3000);
  // RightMotor.freeWheel();
  // delay(3000);
  // RightMotor.forward(200);
  // delay(3000);
  // RightMotor.brake();
  // delay(3000);
  // RightMotor.reverse(200);
  // delay(3000);
  // RightMotor.stop();
  // delay(3000);
  
  // Serial.print(IR1Reading);
  // Serial.print(' ');
  // Serial.print(IR2Reading);
  // Serial.print(' ');
  // Serial.print(IR1DigitalReading * 300);  // *300 for visualising in the plot
  // Serial.print(' ');
  // Serial.print(IR2DigitalReading * 300);
  // Serial.print(' ');
  Serial.print(distance);
  Serial.print(' ');
  Serial.print(distance_expAvg);
  Serial.print(' ');
  Serial.print(distance_ra);
  Serial.print(' ');
  Serial.print(millis() - timestamp);
  Serial.println(' ');

  // delay(100);
 
}
