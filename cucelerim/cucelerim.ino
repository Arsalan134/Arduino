#include "pitches.h"

int melody[] = {
  C4, C4,
  D4, E4, D4, C4,
  C4, C4, C4, C4,
  D4, E4, D4, C4,
  D4, D4, D4, D4,
  E4, F4, E4, D4,
  D4, G4, F4, E4, 
  D4, E4, D4, C4
};

int noteDurations[] = {
  2,2,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
};

void setup() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int) ; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}

void loop() {
  delay(1000);
  setup();
}
