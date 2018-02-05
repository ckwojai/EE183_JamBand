bool R = false;
int counter = 1;
// This is the Ultrasonic Sensor Insturment: act as a leader that send signal to all the others for synchronization
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
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  delay(1000); // Give time for the other MCUs to finish their music 
  Serial.print('R'); // Signal the other MCU that we are starting to play the music
  Serial.print('L');
  // Playing music (LED dance)
  ledflash();
}
