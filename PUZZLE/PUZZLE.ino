/*
  Library examples for TM1638.

  Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the version 3 GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHAqwxxaNTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <TM1638.h>
#include <InvertedTM1638.h>

#define CLK 4
#define DIO 3
#define STB 2
#define hardness 20;

#define pressDelay 300

TM1638 module1(DIO, CLK, STB);
TM1638* module = &module1;

byte mode;
int length, pause, level;

int l = 0;

int sequence[8];

void setup() {
  Serial.begin(9600);

  pause = 500;
  level = 1;

  module->setupDisplay(true, 7);
  mode = 0;
  welcome(&mode);

  Serial.begin(9600);

  randomSeed(analogRead(0));
  delay(1000);
}

void loop() {
  generateRandomSequence();
  showSequence();
  if (!isInputCorrect(&mode)) {
    module->clearDisplay();
    module->setDisplayToString("ERROR ");
    delay(1000);
    setup();

  } else {

    pause -= hardness;

    Serial.println(pause);

    module->clearDisplay();
    module->setDisplayToString("CORRECT ");

 
    for (int i = 128; i > 0; i >>= 1 ) {
      module->setLEDs(i);
      delay(50);
    } 

    for (int i = 1; i < 255; i <<= 1 ) {
      module->setLEDs(i);
      delay(50);
    }
    
    module->setLEDs(0);
    
    delay(200);
    module->clearDisplay();
    String s = String("LEVEL ") + ++level;
    l = 0;
    module->setDisplayToString(s);
    Serial.println(s);
    delay(1000);
    module->clearDisplay();
    delay(1000);
  }
}

void welcome(byte * mode) {

  module->setLEDs(0);
  module->clearDisplay();
  module->setDisplayToString("SELECT");

  byte buttons = module->getButtons();

  while (buttons == 0) {
    buttons = module->getButtons();
    delay(50);
  }

  *mode = buttons;
  length = convertToDecimal(*mode) + 1;
  module -> clearDisplay();

}

void generateRandomSequence() {
  for (int i = 0; i < 8; i++)
    sequence[i] = random(8);
}



boolean isInputCorrect(byte * mode) {
  module->clearDisplay();


  byte buttons = module->getButtons();

  String s = String("");

  for ( int i = 0; i < length; i++) {

    while (buttons == 0) {
      buttons = module->getButtons();
      delay(50);
    }

    s += String(".");

    module->setDisplayToString(s);

    *mode = buttons;
    int pressed = convertToDecimal(*mode);
    module->setLEDs( 1 << (7 - pressed));

    if (sequence[i] != pressed) {
      for (int j = 0; j < 5; j++) {
        module->setLEDs( 1 << (7 - sequence[i]));
        delay(50);
        module->setLEDs(0);
        delay(50);
      }
      return false;
    }

    delay(pressDelay);

    module->setLEDs(0);

    buttons = module->getButtons();
  }

  return true;

}

void showSequence() {
  for (int i = 0; i < length; i++) {
    module->setLEDs( 1 << (7 - sequence[i] ));
    delay(pause);
    module->setLEDs(0);
    delay(pause);
  }
}

int convertToDecimal(byte num) {
  byte k = 1;
  for (int i = 0; i < 8; i++) {
    if ( k == num)
      return i;
    k <<= 1;
  }
  return -1;
}
