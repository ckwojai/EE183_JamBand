const int buzzerPin = 15 ; //Buzzer Input
int duration = 280; //long duration for the buzzer note
int frequency(char note) {
  // Input a note character (a-g), and returns the corresponding frequency in Hz for the tone() function.
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; // key
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523}; // value pari
  // Search and find the corresponding frequency
  for (i = 0; i < numNotes; i++) { // Step through the notes
    if (names[i] == note) {
      return(frequencies[i]);
    }
  }
  return(0);
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  tone(buzzerPin, frequency('c'), duration); // Play note c (262 Hz) for 280ms.
  delay(1000);
} 
