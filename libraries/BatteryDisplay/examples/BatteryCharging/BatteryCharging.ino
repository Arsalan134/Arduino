
#include "TM1651.h"
#define CLK 3//pins definitions for TM1651 and can be changed to other ports       
#define DIO 4
TM1651 batteryDisplay(CLK, DIO);

void setup()
{
  batteryDisplay.init();
  batteryDisplay.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  batteryDisplay.frame(FRAME_ON);//light the frame of the battery display
}

void loop() {
  for (int level = 0; level < 7; level ++) {
    batteryDisplay.displayLevel(level);
    delay(500);
  }
}
