#include <Servo.h>
// GLOBAL VARIABLEs
Servo servo1;
bool R = false;
char Speed = 'H'; // default
char Song = 'W'; // default twinkle
// Ultrasonic
const int trigPin = D5;
const int echoPin = D6;
// Touch sensor
const int touchPin = D2;
// ================================
// ROW THE BOAT 
// ================================
void playRow_servo(int k){
   // K is the only parameter that you need to change to get the different tempos for both the servo and the buzzer.
   // K is better between -30 and 10, any number that is outside this boundary might not work so well.
   // The positive numbers will make it faster and the negative numbers will make it slower.
   int p = 7*k;
   servo1.write(30+k); //let the servo go to the starting position.
   delay(2000); // Wait for 2 seconds and start playing.
         
   servo1.write(70); //The "drum" is fixed at 70 degree in this case.   
   delay(280-p); //By the end of this delay, the servo will reach 70 degree and hit the "drum" .  
   servo1.write(30+k);  //Start getting back to the starting position immediately after hitting the "drum" 
   delay(280-p);   //Reach the starting position by the end of this delay.

   servo1.write(70);  //Start moving toward 70 degree.  
   delay(280-p); //The servo hits the "drum".   
   servo1.write(30+k);  //Start getting back to the starting position immediately after hitting the "drum" 
   delay(280-p);   //Reach the starting position by the end of this delay.
  
   servo1.write(70);    
   delay(280-p);  
   servo1.write(40+k);   
   delay(210-p);   

   servo1.write(70);    
   delay(210-p);       
   servo1.write(50+k);   
   delay(140-p);   
                
   servo1.write(70);
   delay(140-p);   
   servo1.write(30+k);  
   delay(280-p);   

   servo1.write(70);    
   delay(280-p);        
   servo1.write(40+k);    
   delay(210-p);        

   servo1.write(70);    
   delay(210-p);     
   servo1.write(50+k);   
   delay(140-p);       
         
   servo1.write(70);
   delay(140-p);   
   servo1.write(30+k);   
   delay(280-p);         
         
   servo1.write(70);    
   delay(280-p);      
   servo1.write(50+k);   
   delay(140-p);   
             
   servo1.write(70);
   delay(140-p);    
   servo1.write(45+k);   
   delay(800-p);        
         
   servo1.write(70);    
   delay(203-p);         
   servo1.write(50+k);   
   delay(140-p);  
               
   servo1.write(70);
   delay(140-p);  
   servo1.write(50+k);   
   delay(140-p);   
                 
   servo1.write(70);
   delay(140-p);  
   servo1.write(45+k);   
   delay(203-p);         

   servo1.write(70);    
   delay(203-p);         
   servo1.write(50+k);   
   delay(140-p);   
         
   servo1.write(70);
   delay(140-p); 
   servo1.write(50+k);   
   delay(140-p);   
         
   servo1.write(70);
   delay(140-p); 
   servo1.write(45+k);   
   delay(203-p);         
            
   servo1.write(70);    
   delay(203-p);         
   servo1.write(50+k);   
   delay(140-p);   
         
   servo1.write(70);
   delay(140-p);   
   servo1.write(50+k);   
   delay(140-p);   
         
   servo1.write(70);
   delay(140-p);
   servo1.write(45+k);   
   delay(203-p);       
         
   servo1.write(70);    
   delay(203-p);        
   servo1.write(50+k);   
   delay(140-p);   
         
   servo1.write(70);
   delay(140-p);  
   servo1.write(50+k);   
   delay(140-p);   
         
   servo1.write(70);
   delay(140-p);  
   servo1.write(45+k);   
   delay(203-p);       
   
   servo1.write(70);    
   delay(203-p);        
   servo1.write(30+k);    
   delay(280-p);         
   
   servo1.write(70);    
   delay(280-p);         
   servo1.write(50+k);   
   delay(140-p);   
               
   servo1.write(70);
   delay(140-p);   
   servo1.write(30+k);   
   delay(280-p);         

   servo1.write(70);    
   delay(280-p);        
   servo1.write(50+k);   
   delay(140-p);  
         
   servo1.write(70);
   delay(140-p);    
   servo1.write(30+k);   
   
   delay(1000);
}

// FUNCTION FOR THE DRUM
void playTwinkle_servo(int k){
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
void toggleSong(){
  if (Song == 'T') {
    Song = 'W';
  } else if (Song == 'W') {
    Song = 'T';
  }
}
void setup() {
  Serial.begin(115200);
  servo1.attach(D0);  
  servo1.write(30); // lift the stick up and prepare to hit, smaller number = lift; higher number = hit.
  // Ultrasonic 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(touchPin, INPUT); 
}

void loop() {
  
  int distance = ultra_dist();
  Serial.print(distance);
  if (distance > 5) {
    Speed = 'L';
  } else if (distance <5) {
    Speed = 'H';
  }
  int touchValue = digitalRead(touchPin);
  if (touchValue == HIGH) {
      // Serial.println("TOUCHED");
      toggleSong();
    } else {
      Serial.print(".");
    }
  delay(1000); // Give time for the other MCUs to finish their music 
  Serial.print('R'); // Signal the other MCU that we are starting to play the music
  if (Song == 'T') {
    Serial.print('T'); // Low
    if (Speed == 'L') {
     Serial.print('L'); // Low
     playTwinkle_servo(0);
   } else if (Speed == 'H') {
     Serial.print('H'); // High
     playTwinkle_servo(30);
  }
  } else if (Song == 'W') {
      Serial.print('W'); // High
     if (Speed == 'L') {
       Serial.print('L'); // Low
      playRow_servo(-10);
    } else if (Speed == 'H') {
       Serial.print('H'); // High
      playRow_servo(10);
    }
  }
}

