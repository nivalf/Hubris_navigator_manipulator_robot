/*

*/

#define MAX 300
#define UPPER_CUTOFF 0.8*MAX
#define LOWER_CUTOFF 0.6*MAX
 
#define IR1AnalogPin A4 // IR is connected to analog 1
#define IR2AnalogPin A5 // IR is connected to analog 1

float IR1Reading;      // the analog reading from the IR sensor
float IR2Reading;      // the analog reading from the IR sensor

bool IR1State = true;
bool IR2State = true;
 
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

  // Get the average IR reading
  IR1Reading = IR1Reading/count;
  IR2Reading = IR2Reading/count;

  // Set IR state
  IR1State = IR1Reading > UPPER_CUTOFF ? true : IR1Reading < LOWER_CUTOFF ? false : IR1State;
  IR2State = IR2Reading > UPPER_CUTOFF ? true : IR2Reading < LOWER_CUTOFF ? false : IR2State;
  
  Serial.print(IR1State);
  Serial.print(' ');
  Serial.print(IR2State);
  Serial.println(' ');
}
