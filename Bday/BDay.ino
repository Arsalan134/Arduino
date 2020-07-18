#include "pitches.h"

int melody[] = {
  A4, A4 , B4, A4, D5, CS5,
  A4, A4 , B4, A4, E5, D5,
  A4, A4, A5, FS5, D5, CS5, B4,
  G5, G5, FS5, D5, E5, D5 , D6
};

int noteDurations[] = {
  6, 10, 4, 4, 4, 2,
  6, 10, 4, 4, 4, 2,
  6, 10, 4, 4, 4, 4, 3,
  6, 10, 4, 4, 4, 2, 1
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
