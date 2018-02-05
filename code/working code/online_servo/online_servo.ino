#include <Servo.h>
#include <ESP8266WiFi.h>
// GLOBAL VARIABLEs
WiFiServer server(80); //Initialize the server on Port 80
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
// Distance function
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
  // Ultrasonic Setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an 
  // WIFI SETUP 
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
  WiFi.softAP("JamBand", "12345678"); // Provide the (SSID, password); . 
  server.begin(); // Start the HTTP Server
  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
  Serial.print("Server IP is: "); // Print the IP to the monitor window 
  Serial.println(HTTPS_ServerIP);
}

void loop() {
// WIFI CLIENT LOGISTICS: Go To 192.168.4.1
  WiFiClient client = server.available(); 
  String request = client.readStringUntil('\r'); 
  if (request.indexOf("/LOW") != -1){ 
    Speed = 'L';
  } else if (request.indexOf("/HIGH") != -1){ 
    Speed = 'H';
  } else {
    // Online interface has higher priority than physical interaction
     int distance = ultra_dist();
     Serial.print(distance);
      if (distance > 5) {
        Speed = 'L';
      } else if (distance <5) {
       Speed = 'H';
  }
  }
  // Prepare the HTML document to respond and add buttons:
         String s = "HTTP/1.1 200 OK\r\n";
         s += "Content-Type: text/html\r\n\r\n";
         s += "<!DOCTYPE HTML>\r\n<html>\r\n";
         s += "<br><input type=\"button\" name=\"b1\" value=\"SONG LOW\"";
         s += " onclick=\"location.href='/LOW'\">";
         s += "<br><br><br>";
         s += "<br><input type=\"button\" name=\"b1\" value=\"SONG HIGH\"";
         s += " onclick=\"location.href='/HIGH'\">";
         s += "</html>\n";
         //Serve the HTML document to the browser.
         client.flush(); //clear previous info in the stream
         client.print(s); // Send the response to the client
         delay(1);
         // Serial.println("Client disonnected"); //Looking under the hood
  // ACTUALY Serial Communication 
  // delay(1000); // Give time for the other MCUs to finish their music 
  Serial.print('R'); // Signal the other MCU that we are starting to play the music
  if (Speed == 'L') {
    Serial.print('L'); // Low
    playDrum(0);
  } else if (Speed == 'H') {
    Serial.print('H'); // High
    playDrum(30);
  }
}

