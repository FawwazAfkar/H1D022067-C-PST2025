#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

// define the pins for the LEDs
int redLED = D0;
int yellowLED = D1;
int greenLED = D2;

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);

  // initialize the pins as output
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //sequence of traffic lights
  //red
  digitalWrite(redLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  //yellow
  digitalWrite(yellowLED, HIGH);
  delay(500);
  digitalWrite(yellowLED, LOW);
  //green
  digitalWrite(greenLED, HIGH);
  delay(500);
  digitalWrite(greenLED, LOW);
}


// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }