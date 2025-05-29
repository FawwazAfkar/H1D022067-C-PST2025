#include <Arduino.h>

/*
 * Water Level Monitoring System
 * This code reads the water level from a sensor and controls LEDs and a buzzer based on the water level.
 * - Green LED: Low water level
 * - Yellow LED: Medium water level
 * - Red LED: High water level (danger)
 * - Buzzer: Sounds when water level is high
 */

// Pin definitions
const int waterLevelPin = A0;     // Water level sensor connected to A0
const int buzzerPin = D5;         // Buzzer connected to D5
const int redLedPin = D1;         // Red LED connected to D1
const int yellowLedPin = D2;      // Yellow LED connected to D2
const int greenLedPin = D3;       // Green LED connected to D3

// Threshold values (adjust according to your sensor)
const int lowThreshold = 300;     // Low water level threshold
const int mediumThreshold = 600;  // Medium water level threshold
// Note: Adjust these thresholds based on your specific sensor and calibration

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(waterLevelPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  
  // Turn off all LEDs and buzzer initially
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  Serial.println("Water Level Monitoring System Started");
}

void loop() {
  // Read water level sensor value
  int sensorValue = analogRead(waterLevelPin);
  
  // Print the sensor value to serial monitor
  Serial.print("Water Level Sensor Value: ");
  Serial.println(sensorValue);
  
  // Determine water level and control LEDs/buzzer
  if (sensorValue < lowThreshold) {
    // Low water level - Green LED
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    Serial.println("Status: Low Water Level");
  } 
  else if (sensorValue >= lowThreshold && sensorValue < mediumThreshold) {
    // Medium water level - Yellow LED
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    Serial.println("Status: Medium Water Level");
  } 
  else {
    // High water level - Red LED and buzzer
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Status: HIGH Water Level - WARNING!");
  }
  
  // Delay between readings
  delay(1000);
}