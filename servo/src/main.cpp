#include <Arduino.h>
#include <Servo.h>

// var
Servo MyServo;


void setup() {
  // put your setup code here, to run once:
  MyServo.attach(D5);
}

void loop() {
  // put your main code here, to run repeatedly:
  // for (int pos = 0; pos < 180; pos++) {
  //   MyServo.write(pos);
  //   delay(10);
  // }
  // for (int pos = 180; pos >= 0; pos--) {
  //   MyServo.write(pos);
  //   delay(10);
  // }
  MyServo.write(180);
  delay(1000);
  MyServo.write(0);
  delay(1000);
  MyServo.write(180);
  delay(1000);
}

// put function definitions here:
