int touchPin = D2;
void setup() {
  Serial.begin(115200);
  pinMode(touchPin, INPUT); 
}
void loop() {
  int touchValue = digitalRead(touchPin);
    if (touchValue == HIGH) {
      Serial.println("TOUCHED");
    } else {
      Serial.print(".");
    }
    delay(1000);
}
