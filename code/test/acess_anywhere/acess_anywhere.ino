#include <ESP8266WiFi.h>

const char* ssid = "102-2.4";
const char* password = "andrewwilliam";
const char* host = "192.168.4.2"; //it will tell you the IP once it starts up
                                        //just write it here afterwards and upload

WiFiServer server(90); //Initialize the server on Port 80

void setup() {

WiFi.mode(WIFI_STA); //Our ESP8266-12E is an AccessPoint 
//WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); . 
// server.begin(); // Start the HTTP Server
//IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
//Serial.print("Server IP is: "); // Print the IP to the monitor window 
//Serial.println(HTTPS_ServerIP);
Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
// Start the server
server.begin();
Serial.println("Server started");
// Print the IP address
Serial.println(WiFi.localIP());
pinMode(LED_BUILTIN, OUTPUT); //GPIO16 is an OUTPUT pin;
digitalWrite(LED_BUILTIN, LOW); //Initial state is ON
}

void loop() {
//Looking under the hood
WiFiClient client = server.available();
if (!client) { 
return; 
} 
//Looking under the hood 
Serial.println("Somebody has connected :)");
//Read what the browser has sent into a String class and print the request to the monitor
String request = client.readStringUntil('\r'); 
//Looking under the hood 
Serial.println(request);
// Handle the Request
if (request.indexOf("/OFF") != -1){ 
digitalWrite(LED_BUILTIN, HIGH); }
else if (request.indexOf("/ON") != -1){ 
digitalWrite(LED_BUILTIN, LOW); 
}
  // Prepare the HTML document to respond and add buttons:
         String s = "HTTP/1.1 200 OK\r\n";
         s += "Content-Type: text/html\r\n\r\n";
         s += "<!DOCTYPE HTML>\r\n<html>\r\n";
         s += "<br><input type=\"button\" name=\"b1\" value=\"LED On\"";
         s += " onclick=\"location.href='/ON'\">";
         s += "<br><br><br>";
         s += "<br><input type=\"button\" name=\"b1\" value=\"LED Off\"";
         s += " onclick=\"location.href='/OFF'\">";
         s += "</html>\n";
         //Serve the HTML document to the browser.
         client.flush(); //clear previous info in the stream
         client.print(s); // Send the response to the client
         delay(1);
         Serial.println("Client disonnected"); //Looking under the hood
}


