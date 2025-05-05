#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definisikan pin SDA dan SCL
int SDA_pin = D5;
int SCL_pin = D6;

// Lirik lagu
const char* lyrics[] = {
  "sudah terbiasa terjadi tante",
  "teman datang ketika",
  "lagi butuh saja",
  "coba kalo lagi susah",
  "mereka semua menghilangggg",
};

const int numLines = sizeof(lyrics) / sizeof(lyrics[0]);

void setup() {
  Wire.begin(SDA_pin, SCL_pin);
  lcd.init();
  lcd.backlight();
}

void printTyping(const char* text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  int len = strlen(text);
  int row = 0;
  int col = 0;
  
  for (int i = 0; i < len; i++) {
    lcd.print(text[i]);
    col++;
    if (col >= 16) {
      row++;
      if (row > 1) {
        // Kalau lebih dari 2 baris, berhenti
        break;
      }
      lcd.setCursor(0, row);
      col = 0;
    }
    delay(100); // Delay antar karakter, bisa diubah kecepatannya
  }
}

void loop() {
  for (int i = 0; i < numLines; i++) {
    printTyping(lyrics[i]);
    delay(1500); // Tunggu sebelum lanjut ke baris berikutnya
  }
}
