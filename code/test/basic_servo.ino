#include <Servo.h>
Servo servo1;
void setup() {
  // put your setup code here, to run once:
  servo1.attach(16); // 16GPIN for servo
}

void loop() {
  // put your main code here, to run repeatedly:
 servo1.write(90);
 delay(500);
 servo1.write(0);
 delay(500);
}
