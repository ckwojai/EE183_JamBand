int touchPin = D2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(touchPin, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int touchValue = digitalRead(touchPin);
    if (touchValue == HIGH) {
      Serial.println("TOUCHED");
    } else {
      Serial.print(".");
    }
    delay(1000);
}
