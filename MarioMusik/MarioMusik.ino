#include "pitches.h"
#include "melody.h"
#define melodyPin 8

void setup() {
  pinMode(melodyPin, OUTPUT);
  Serial.begin(9600);
  if (sizeof(underworld_melody) != sizeof(melody)) {
    return;
  }
}

void loop() {
  marioTheme();
  marioTheme();
  underworldTheme();
}

void marioTheme() {
  Serial.println("\"Mario Theme\"");
  int size = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo[thisNote];
    tone(melodyPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 2;
    delay(pauseBetweenNotes);
    noTone(melodyPin);
  }
}

void underworldTheme() {
  Serial.println("\"Underworld Theme\"");
  int size = sizeof(underworld_melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / underworld_tempo[thisNote];
    tone(melodyPin, underworld_melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 2;
    delay(pauseBetweenNotes);
    noTone(melodyPin);
  }
}



