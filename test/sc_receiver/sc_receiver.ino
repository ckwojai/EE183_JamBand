int incomingByte;      // a variable to read incoming serial data into
bool R = false;
char Speed = 'N'; // no signal recieved yet by default
void ledflash() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(250);                      // Wait for two seconds (to demonstrate the active low LED)
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);
}
void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
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
          ledflash();
          R = false;
          Speed = 'N';
          Serial.flush();
        } 
       
      } else {
        Serial.println("Waiting for Ready Signal...");
      }
}   


