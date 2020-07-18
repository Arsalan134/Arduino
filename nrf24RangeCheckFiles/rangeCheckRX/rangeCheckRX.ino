#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

const uint64_t pipeIn =  0xE8E8F0F0E1LL;
const byte serialHeader[4] = {255,254,253,252};

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
  Serial.begin(9600);
  printf_begin();
    
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
  
  radio.printDetails();
}

unsigned long lastReportTime = 0;
int count = 0;

void loop()
{
  while ( radio.available() ) {        
    radio.read(&data, sizeof(MyData));
    count++;
  }

  unsigned long now = millis();
  if ( now - lastReportTime > 1000 ) {
    Serial.write((uint8_t*)serialHeader, 4);
    Serial.write((uint8_t*)&count, sizeof(count));
    //Serial.println(count);
    lastReportTime = now;
    count = 0;
  }
}

