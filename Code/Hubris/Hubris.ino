#include "IR.h"

#define IRLeftAPin A4
#define IRRightAPin A5

float IR1Reading;      // the analog reading from the IR sensor
float IR2Reading;      // the analog reading from the IR sensor

IR IRLeft(IRLeftAPin);
IR IRRight(IRRightAPin);
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void) {

  IR1Reading = IRLeft.read();
  IR2Reading = IRRight.read();
  
  Serial.print(IR1Reading);
  Serial.print(' ');
  Serial.print(IR2Reading);
  Serial.println(' ');

  delay(100);
 
}
