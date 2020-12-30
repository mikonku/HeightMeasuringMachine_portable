
/*
Sensor jarak HC-SR04
pin yang perlu dihubungkan
VCC to arduino 5v
GND to arduino GND
Echo to Arduino pin 7
Trig to Arduino pin 8

*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "emrizkis";
const char* password = "rizki123";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
String text = "";
double data1, data;
 
const int echoPin =16; //Echo Pin
const int trigPin =5; //Trigger Pin
 
int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long cal, duration, distance; //waktu untuk kalkulasi jarak
 
void setup() {
delay(1000);
 Serial.begin(115200);
 WiFi.begin(ssid, password); //begin WiFi connection
 Serial.println("");
 
 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
}
 
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 server.on("/data.txt", [](){
   text = (String)data;
   server.send(200, "text/html", text);
 });
server.on("/LED1ON", []() {
    server.send(200, "text/html", page);
    Serial.print("Callibrate");
    calibrate();
    delay(1000);
   server.on("/", [](){
   page = "<h1>Your High</h1><h1>ini cm:</h1> <h1 id=\"data\">""</h1>\r\n";
   page += "<script>\r\n";
   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
   page += "function loadData(url, callback){\r\n";
   page += "var xhttp = new XMLHttpRequest();\r\n";
   page += "xhttp.onreadystatechange = function(){\r\n";
   page += " if(this.readyState == 4 && this.status == 200){\r\n";
   page += " callback.apply(xhttp);\r\n";
   page += " }\r\n";
   page += "};\r\n";
   page += "xhttp.open(\"GET\", url, true);\r\n";
   page += "xhttp.send();\r\n";
   page += "}\r\n";
   page += "function updateData(){\r\n";
   page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   page+= "<p>Pengkalibrasi:  ";
   page+= "<a href=\"LED1ON\"\"><button>Kalibrasi</button></a></p><br>";
  
   server.send(200, "text/html", page);
});
    });
    
server.on("/LED1OFF", []() {
    server.send(200, "text/html", page);
    Serial.print("Done");
    delay(1000);
  });
 
 server.on("/", [](){
   page = "<h1>Your High</h1><h1>ini cm:</h1> <h1 id=\"data\">""</h1>\r\n";
   page += "<script>\r\n";
   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
   page += "function loadData(url, callback){\r\n";
   page += "var xhttp = new XMLHttpRequest();\r\n";
   page += "xhttp.onreadystatechange = function(){\r\n";
   page += " if(this.readyState == 4 && this.status == 200){\r\n";
   page += " callback.apply(xhttp);\r\n";
   page += " }\r\n";
   page += "};\r\n";
   page += "xhttp.open(\"GET\", url, true);\r\n";
   page += "xhttp.send();\r\n";
   page += "}\r\n";
   page += "function updateData(){\r\n";
   page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   page+= "<p>Pengkalibrasi:  ";
   page+= "<a href=\"LED1ON\"\"><button>Kalibrasi</button></a></p><br>";
  
   server.send(200, "text/html", page);
});
 
 server.begin();
 Serial.println("Web server started!");
 calibrate();
 }
 
void loop() {
  sens(trigPin,echoPin);
  delay(1000);
  server.handleClient();
}

void sens(int trigPin, int echoPin){
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  
  digitalWrite(trigPin, LOW);delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  //perhitungan untuk dijadikan jarak

  data=data1-duration/58.2;
  
}

void calibrate(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  
  digitalWrite(trigPin, LOW);delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  //perhitungan untuk dijadikan jarak
  data1 = duration/58.2;
  Serial.println(data1);
  delay(500);
}

