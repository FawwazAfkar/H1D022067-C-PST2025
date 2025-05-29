#include <Arduino.h>

// Pin definitions
const int buzzerPin = D0; // Connect buzzer to pin 8
const int ledPin = D1;   // Connect LED to pin 13

// Notes frequencies (in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988


// Melody for "Happy Birthday"
int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, // Happy Birthday to You
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5, // Happy Birthday to You
  NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4, // Happy Birthday Dear [Name]
  NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5  // Happy Birthday to You
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 8, 4, 4, 4, 2, // Happy Birthday to You
  4, 8, 4, 4, 4, 2, // Happy Birthday to You
  4, 8, 4, 4, 4, 8, 2, // Happy Birthday Dear [Name]
  4, 8, 4, 4, 4, 2  // Happy Birthday to You
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Play the melody
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = (1000 / noteDurations[i]) * 1.5; // Increase duration by 1.5x
    tone(buzzerPin, melody[i], noteDuration);

    // Blink the LED in sync with the note
    digitalWrite(ledPin, HIGH);
    delay(noteDuration / 2); // LED on for half the note duration
    digitalWrite(ledPin, LOW);
    delay(noteDuration / 2); // LED off for the other half

    // Pause between notes
    delay(50);
  }
}

void loop() {
  // Nothing to do here
}