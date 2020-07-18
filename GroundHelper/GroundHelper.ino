#include <Wire.h>
#include <SPI.h>
#include "Timer.h"
#include "TM1651.h"

#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "Grove_LED_Bar.h"

bool printAngle, printTouch;

bool emergencyStop = false;

const byte delayTime = 10;

byte batteryPin = A2;

boolean timeout = true;

Timer t;

byte minutes  = 0;
byte seconds  = 0;
bool turnOnColon = false;

TM1651 airplaneBatteryDisplay(2, 3);
SevenSegmentExtended timerDisplay(5, 6);
TM1651 groundBatteryDisplay(10, 9);
Grove_LED_Bar signalStrengthDisplay(9, 10, 0); // pins collide ???

void setup() {
  delay(100);
  Serial.begin(9600);

  timerDisplay.begin();
  timerDisplay.setBacklight(10);

  delay(100);
  
  airplaneBatteryDisplay.init();
  groundBatteryDisplay.init();

  delay(100);

  signalStrengthDisplay.begin();

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 64911;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();

  groundBatteryDisplay.set(1); // 0...7 brigthness
  airplaneBatteryDisplay.set(1);

}


ISR(TIMER1_OVF_vect) {

  minutes += seconds / 59;
  seconds = ++seconds % 60;

  timerDisplay.printTime(minutes, seconds);
  turnOnColon = !turnOnColon;
  timerDisplay.setColonOn(turnOnColon);

  int batteryLevel = map(analogRead(batteryPin), 0, 310, 0, 7);
  groundBatteryDisplay.displayLevel(batteryLevel);

  Serial.println(analogRead(batteryPin));
}

void loop() {

}
