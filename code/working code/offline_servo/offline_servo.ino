#include <Servo.h>
// GLOBAL VARIABLEs
Servo servo1;
bool R = false;
char Speed = 'L'; // default
// Ultrasonic
const int trigPin = D5;
const int echoPin = D6;

// FUNCTION FOR THE DRUM
void playDrum(int k){
  int p=7*k; //I've figured out that it takes about 7ms for the servo to rotate 1 degree.
  for (int j=0; j<2; j++) { //j = how many times to play this 7 beats
    for(int i=0;i<7;i++) // the constants below are obtained by trials and errors
  {   
    servo1.write(90+k);   
    delay(300-p);         
    servo1.write(70);  
    delay(300-p);   
  }
  delay(900-p);
  }
}
int ultra_dist(){
  long duration;
  int distance;
  // Ultarsonic 
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
  distance= duration*0.034/2;
  return distance;
}

void setup() {
  Serial.begin(115200);
  servo1.attach(D0);  
  servo1.write(30); // lift the stick up and prepare to hit, smaller number = lift; higher number = hit.
  // Ultrasonic 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  int distance = ultra_dist();
  Serial.print(distance);
  if (distance > 5) {
    Speed = 'L';
  } else if (distance <5) {
    Speed = 'H';
  }
  delay(1000); // Give time for the other MCUs to finish their music 
  Serial.print('R'); // Signal the other MCU that we are starting to play the music
  if (Speed == 'L') {
    Serial.print('L'); // Low
    playDrum(0);
  } else if (Speed == 'H') {
    Serial.print('H'); // High
    playDrum(30);
  }
}

