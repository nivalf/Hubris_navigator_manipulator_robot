
 
int IR1AnalogPin = A4; // IR is connected to analog 1
int IR2AnalogPin = A5; // IR is connected to analog 1
float IR1Reading;      // the analog reading from the IR sensor
float IR2Reading;      // the analog reading from the IR sensor
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void) {
  int count = 100;

  IR1Reading = 0;
  IR2Reading = 0;

  for(int i=0; i<count; i++) {
    IR1Reading += analogRead(IR1AnalogPin);
    IR2Reading += analogRead(IR2AnalogPin);
    delay(1);
  }

  // Get the average value
  IR1Reading = IR1Reading/count;
  IR2Reading = IR2Reading/count;
  
  Serial.print(IR1Reading);
  Serial.print(' ');
  Serial.print(IR2Reading);
  Serial.println(' ');
}
