#include <SoftwareSerial.h>

SoftwareSerial a(2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  a.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String input = Serial.readString();
    a.println(input);
  }

  if (a.available() > 1) {
    String input = a.readString();
    Serial.println(input);
  }
  delay(20);
}
