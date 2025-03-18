#include <Arduino.h>

//pin var declaration
int echoPin = D0; // Echo Pin
int trigPin = D1; // Trigger Pin
int redledPin = D8; // Red LED Pin
int yellowledPin = D7; // Yellow LED Pin

// Distance variables
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(redledPin, OUTPUT); // Sets the ledPin as an Output
  pinMode(yellowledPin, OUTPUT); // Sets the ledPin as an Output

  Serial.begin(9600); // Starts the serial communication
  }

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // set the distance to turn on the LED
  if (distance <= 10) {
    digitalWrite(redledPin, HIGH);
    digitalWrite(yellowledPin, LOW);
  } else if (distance > 10 && distance <= 20) {
    digitalWrite(redledPin, LOW);
    digitalWrite(yellowledPin, HIGH);
  }else {
    digitalWrite(redledPin, LOW);
    digitalWrite(yellowledPin, LOW);
  }

  delay(500);
}
