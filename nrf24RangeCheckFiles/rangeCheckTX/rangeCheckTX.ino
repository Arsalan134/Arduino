#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

const uint64_t pipe =  0xE8E8F0F0E1LL;

RF24 radio(9, 10);

struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte dial1;
  byte dial2;
  byte switches; // bitflag
};

MyData data;

void setup()
{ 
  Serial.begin(57600);
  printf_begin();
    
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);

  radio.openWritingPipe(pipe);
  
  radio.printDetails();
  
  data.throttle = 64;
  data.yaw = 64;
  data.pitch = 128;
  data.roll = 192;
}

void loop()
{  
  analogRead(A0);
  analogRead(A1);
  analogRead(A2);
  analogRead(A3);
  
  radio.write(&data, sizeof(MyData));
}

