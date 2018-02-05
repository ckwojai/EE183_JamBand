int incomingByte;      // a variable to read incoming serial data into
bool R = false;
char Speed = 'N'; // no signal recieved yet by default
void setup() {
  // initialize serial communication:
  Serial.begin(115200);
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) { // This is to check if Ready to play or not
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    char signal = char(incomingByte);
    Serial.println(signal);
    if (signal == 'R') {
      R = true; // Ready signal received, set R to be true
    }
    }
  if (R) { // The following code runs only when R is true
     // Just know ready to play is not enough, we still need to know in what speed we are playing
      Serial.println("Waiting for Speed Signal...");
      delay(1000);
     if (Serial.available() > 0) {
        incomingByte = Serial.read();
        char signal = char(incomingByte);
        Serial.println(signal);
        if (signal == 'L') { // play it slow
          Speed = 'L';
        } else if (signal == 'H') { // play it high
          Speed = 'H';
        }
        }
      if (Speed == 'N') {
        // Do nothing because Speed signal not received yet;
      } else {
          Serial.println("Playing music now for 3 seconds...");
          delay(3000);
          Serial.println("Finished playing music");
          R = false;
          Speed = 'N';
          Serial.flush();
        } 
       
      } else {
        Serial.println("Waiting for Ready Signal...");
        delay(1000);
      }
}   


