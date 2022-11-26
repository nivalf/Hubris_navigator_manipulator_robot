#include "IR.h"

#define IRLeftAPin A4
#define IRRightAPin A5

float IR1Reading;      // the analog reading from the IR sensor
float IR2Reading;      // the analog reading from the IR sensor

bool IR1DigitalReading;
bool IR2DigitalReading;

IR IRLeft(IRLeftAPin);
IR IRRight(IRRightAPin);
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor

  IRLeft.init();
  IRRight.init();
}
 
void loop(void) {

  IR1Reading = IRLeft.read();
  IR2Reading = IRRight.read();

  IR1DigitalReading = IRLeft.digitalRead();
  IR2DigitalReading = IRRight.digitalRead();
  
  Serial.print(IR1Reading);
  Serial.print(' ');
  Serial.print(IR2Reading);
  Serial.print(' ');
  Serial.print(IR1DigitalReading*300);
  Serial.print(' ');
  Serial.print(IR2DigitalReading*300);
  Serial.println(' ');

  // delay(1);
 
}
