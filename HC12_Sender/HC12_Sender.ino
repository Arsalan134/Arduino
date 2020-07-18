
// Sender

#include "SoftwareSerial.h"

SoftwareSerial HC12(10, 11);

void setup() {
  Serial.begin(9600);
  HC12.begin(115200);
}

char b = 0;
int d = 1000;

void loop() {
  Serial.print("I send: ");

  b = '0';
  
  Serial.println(b);
  HC12.print(b);
  HC12.println(b);
  HC12.write(b);
  delay(d);

  b = '1';
  
  Serial.print("I send: ");
  Serial.println(b);
  HC12.print(b);
  HC12.println(b);
  HC12.write(b);
  delay(d);
}
