#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
/*
 * =================================================================
 * Sistem Deteksi Dini Banjir Standalone (Tanpa Koneksi Internet)
 * =================================================================
 * Deskripsi:
 * Kode ini membaca jarak dari sensor ultrasonik untuk mendeteksi ketinggian air.
 * Berdasarkan ketinggian tersebut, sistem akan mengontrol 3 LED dan 1 Buzzer
 * sebagai indikator status bahaya banjir.
 * * Versi ini sudah diperbaiki dengan menambahkan Function Prototypes.
 * =================================================================
 */

// --- Definisi Pin Hardware ---
const int PIN_TRIG = D1; // GPIO5
const int PIN_ECHO = D2; // GPIO4

const int PIN_LED_HIJAU = D5;  // GPIO14
const int PIN_LED_KUNING = D6; // GPIO12
const int PIN_LED_MERAH = D7;  // GPIO13
const int PIN_BUZZER = D8;     // GPIO15

// --- Logika Deteksi Banjir ---
const float JARAK_ALAT_KE_TANAH = 100.0;
const float BATAS_JARAK_WASPADA = 95.0; 
const float BATAS_JARAK_BAHAYA = 90.0;  

// Variabel untuk timer buzzer Waspada
unsigned long waktuBuzzerSebelumnya = 0;
bool statusBuzzer = LOW;


// =================================================================
// >>>>> BAGIAN YANG DIPERBAIKI ADA DI SINI <<<<<
// --- Deklarasi Fungsi (Function Prototypes) ---
// Memberitahu compiler tentang fungsi yang akan digunakan.
float ukurJarakCm();
void statusAman();
void statusWaspada();
void statusBahaya();
// =================================================================


void setup() {
  // Mulai komunikasi serial untuk debugging di Serial Monitor
  Serial.begin(9600);
  delay(100);

  // Atur mode untuk setiap pin
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED_HIJAU, OUTPUT);
  pinMode(PIN_LED_KUNING, OUTPUT);
  pinMode(PIN_LED_MERAH, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  // Pastikan semua output mati pada saat pertama kali dinyalakan
  digitalWrite(PIN_LED_HIJAU, LOW);
  digitalWrite(PIN_LED_KUNING, LOW);
  digitalWrite(PIN_LED_MERAH, LOW);
  digitalWrite(PIN_BUZZER, LOW);

  Serial.println("==========================================");
  Serial.println("Sistem Deteksi Banjir Standalone Dimulai");
  Serial.println("==========================================");
}

void loop() {
  // 1. Panggil fungsi untuk mengukur jarak
  float jarakCm = ukurJarakCm();
  
  // 2. Hitung perkiraan ketinggian air untuk ditampilkan di Serial Monitor
  float ketinggianAir = JARAK_ALAT_KE_TANAH - jarakCm;
  if (ketinggianAir < 0) {
    ketinggianAir = 0;
  }

  // 3. Tampilkan hasil pembacaan di Serial Monitor
  Serial.print("Jarak Terbaca: ");
  Serial.print(jarakCm);
  Serial.print(" cm  |  Perkiraan Ketinggian Air: ");
  Serial.print(ketinggianAir);
  Serial.println(" cm");

  // 4. Tentukan status bahaya berdasarkan jarak yang terbaca
  if (jarakCm > BATAS_JARAK_WASPADA) {
    statusAman();
  } 
  else if (jarakCm <= BATAS_JARAK_WASPADA && jarakCm > BATAS_JARAK_BAHAYA) {
    statusWaspada();
  } 
  else if (jarakCm <= BATAS_JARAK_BAHAYA) {
    if (jarakCm > 0) {
      statusBahaya();
    } else {
      statusAman(); 
    }
  }

  delay(1000); 
}

/**
 * @brief Mengukur jarak menggunakan sensor HC-SR04.
 * @return Jarak dalam satuan sentimeter (cm).
 */
float ukurJarakCm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  long durasi = pulseIn(PIN_ECHO, HIGH, 30000);
  
  return durasi * 0.0343 / 2.0;
}

// --- Kumpulan Fungsi untuk Mengatur Status ---

void statusAman() {
  Serial.println("Status: AMAN");
  digitalWrite(PIN_LED_HIJAU, HIGH);
  digitalWrite(PIN_LED_KUNING, LOW);
  digitalWrite(PIN_LED_MERAH, LOW);
  digitalWrite(PIN_BUZZER, LOW);
}

void statusWaspada() {
  Serial.println("Status: WASPADA");
  digitalWrite(PIN_LED_HIJAU, LOW);
  digitalWrite(PIN_LED_KUNING, HIGH);
  digitalWrite(PIN_LED_MERAH, LOW);

  if (millis() - waktuBuzzerSebelumnya >= 1500) { 
    waktuBuzzerSebelumnya = millis();
    statusBuzzer = !statusBuzzer; 
    digitalWrite(PIN_BUZZER, statusBuzzer);
  }
}

void statusBahaya() {
  Serial.println("Status: BAHAYA");
  digitalWrite(PIN_LED_HIJAU, LOW);
  digitalWrite(PIN_LED_KUNING, LOW);
  digitalWrite(PIN_LED_MERAH, HIGH);
  digitalWrite(PIN_BUZZER, HIGH); 
}
