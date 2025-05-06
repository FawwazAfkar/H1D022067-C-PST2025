#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "wawiz"; // your network SSID (name)
const char* password = "satusampaisembilan"; // your network password

ESP8266WebServer server(80); // Create a web server on port 80
String webpage;

void setup() {
  Serial.begin(9600); // Start the Serial communication
  delay(10);

  pinMode(D2, OUTPUT); // Set D2 pin as output
  pinMode(D3, OUTPUT); // Set D3 pin as output
  pinMode(D4, OUTPUT); // Set D4 pin as output

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Configuring access point...");

  // Mengatur wifi
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);

  //print status connect
  Serial.println("Connecting to ");
  Serial.println(WiFi.softAPIP());

  // Isi webpage
  webpage += "<html><body><h1>Web Control ESP 8266 by wawiz</h1>";
  webpage += "<p>LED 1 : ";
  webpage += "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a></p><br>";
  webpage += "<p>LED 2 : ";
  webpage += "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a></p><br>";
  webpage += "<p>LED 3 : ";
  webpage += "<a href=\"LED3ON\"\"><button>ON</button></a><a href=\"LED3OFF\"\"><button>OFF</button></a></p>";

  // membuat tampilan webpage
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Bagian ini untuk merespon perintah yang masuk
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(D2, HIGH); // Turn LED on
    delay(1000);
  });
  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(D2, LOW); // Turn LED off
    delay(1000);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(D3, HIGH); // Turn LED on
    delay(1000);
  });
  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(D3, LOW); // Turn LED off
    delay(1000);
  });
  server.on("/LED3ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(D4, HIGH); // Turn LED on
    delay(1000);
  });
  server.on("/LED3OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(D4, LOW); // Turn LED off
    delay(1000);
  });

  // Start the server
  server.begin();
  Serial.println("Web server dijalankan");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); // Handle client requests
}
