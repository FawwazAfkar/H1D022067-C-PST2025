#include <Arduino.h>
#include <Wire.h>

int SDA_pin = D5;
int SCL_pin = D6;

void setup() {
  Wire.begin(SDA_pin, SCL_pin); // Initialize I2C with custom SDA and SCL pins
  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  // put your main code here, to run repeatedly:
  byte error, address;
  int nDevices;
  Serial.print("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) 
    {
      Serial.print("I2C terbaca pada alamat 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("!");
      nDevices++;
    } 
    else if (error == 4) 
    {
      Serial.print("error tidak diketahui pada alamat 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("Tidak ada alamat I2C yang ditemukan \n");
  } else {
    Serial.println("selesai \n");
  }
  delay(5000); // Wait 5 seconds for the next scan
}
