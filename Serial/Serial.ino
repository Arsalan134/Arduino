
#include "SoftwareSerial.h"

SoftwareSerial HC12(10, 11);

void setup() {
  Serial.begin(9600);
  HC12.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

char b = 0;

void loop() {
  if (HC12.available() > 0) {
    b = HC12.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(b);
    if (b == '1') {
      digitalWrite(LED_BUILTIN, HIGH);
    } else if ( b == '0') {
      digitalWrite(LED_BUILTIN, LOW);
    }
//    Serial.flush();
  }
  delay(10);
}
