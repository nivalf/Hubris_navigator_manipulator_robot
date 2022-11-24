// defines pins numbers
const int trigPin = 9;
const int echoPin = 10; // set to A3

const int count = 100;
// defines variables
long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // clear
  distance = 0.0;

  // Get count number of distance readings & accumilate
  for (int i = 0; i<count; i++) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance += duration * 0.034 / 2.0;
  }

  // avg
  distance = distance/count;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance:");
  Serial.println(distance);
}