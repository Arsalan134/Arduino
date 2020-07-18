/*
  SD card file dump

  This example shows how to read a file from the SD card using the
  SD library and send it over the serial port.

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  22 December 2010
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

//#include <stdint.h>
//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <avr/pgmspace.h>
//#include "sounddata.h"

const int chipSelect = 10;

int speakerPin = A3; // Can be either 3 or 11, two PWM outputs connected to Timer 2

void setup() {
  // Open serial communications and wait for port to open:
//  Serial.begin(115200);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

//  startPlayback();
  pinMode(speakerPin, OUTPUT);
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("fademono.wav");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      delayMicroseconds(17);
      analogWrite(speakerPin, dataFile.read());
    }
    dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  Serial.println("Salam");
}

void loop() {
}

