// GLOBAL VARIABLES
int speakerPin = 15 ; //Buzzer Input
int length = 15; // the number of notes// was 15 before
int incomingByte;      // a variable to read incoming serial data into
bool R = false;
char Speed = 'N'; // no signal recieved yet by default
//twinkle twinkle little star
// char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
char notes[] = "ccggaag ffeeddc"; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 4};
// DEFINE FUNCTIONS FOR TWINKLE LITTEL STAR
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
void playSong(int tempo){
    for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    // pause between notes
    delay(tempo / 1); 
  }
}
void setup() {
  pinMode(speakerPin, OUTPUT);
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
      } else if (Speed == 'L') {
          playSong(300);
          // Reset
          R = false;
          Speed = 'N';
          Serial.flush();
        } else if (Speed == 'H') {
          playSong(110);
          // Reset
          R = false;
          Speed = 'N';
          Serial.flush();
        }
       
      } else {
        Serial.println("Waiting for Ready Signal...");
      }
  } 
