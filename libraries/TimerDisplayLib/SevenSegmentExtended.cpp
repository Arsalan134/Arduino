#include "SevenSegmentExtended.h"


SevenSegmentExtended::SevenSegmentExtended(uint8_t pinClk, uint8_t pinDIO) :
  SevenSegmentTM1637(pinClk, pinDIO)
{ };


void SevenSegmentExtended::printTime(uint8_t hour, uint8_t min) {

  uint8_t buffer[4];

  buffer[0] = encode(int16_t(hour / 10));
  buffer[1] = encode(int16_t(hour % 10));
  buffer[2] = encode(int16_t(min / 10));
  buffer[3] = encode(int16_t(min % 10));

  printRaw(buffer, 4, 0);
}

// positive counter 0..99, negative counter 0..-9
void SevenSegmentExtended::printDualCounter(int8_t leftCounter, int8_t rightCounter, bool zeroPadding) {

  int8_t max = 99;
  int8_t min = -9;
  uint8_t zeroByte = encode('0');

  leftCounter = (leftCounter > max)?max:leftCounter;
  leftCounter = (leftCounter < min)?min:leftCounter;
  rightCounter = (rightCounter > max)?max:rightCounter;
  rightCounter = (rightCounter < min)?min:rightCounter;

  Serial.println(leftCounter);
  Serial.println(rightCounter);


  bool colonWasOn = getColonOn();     // get current state
  setColonOn(true);                   // turn on the colon
  home();                             // set cursor to zero

  if ( leftCounter < 10 && leftCounter >= 0) {
    if ( zeroPadding ) {
      printRaw(zeroByte,1);
      setCursor(0,1);
    } else {
      // print colon
      printRaw(TM1637_COLON_BIT,1);
    };
  };
  print(leftCounter);

  if ( rightCounter < 10 && rightCounter >= 0) {
    if ( zeroPadding ) {
      printRaw(zeroByte,2);
    }
    uint8_t pos = 2;
    printRaw(0,pos);
    setCursor(0,3);
  } else {
    setCursor(0,2);
  }
  print(rightCounter);

  // set to previous state
  setColonOn(colonWasOn);
};
