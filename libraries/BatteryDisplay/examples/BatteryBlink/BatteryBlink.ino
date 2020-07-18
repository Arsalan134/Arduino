
#include "TM1651.h"
#define CLK 4
#define DIO 3
TM1651 batteryDisplay(CLK, DIO);
void setup() {
  batteryDisplay.init();
  batteryDisplay.set(7);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void loop() {
  for (int i = 0 ; i <= 7 ; i ++) {
    batteryDisplay.displayLevel(i);
    delay(100);
  }
}
