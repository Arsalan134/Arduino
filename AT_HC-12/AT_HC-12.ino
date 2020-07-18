//HC-12 AT Commander
//Autor Tom Heylen tomtomheylen.com
//The HC-12 commander mode runs at baud rate 9600

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // TX, RX

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  mySerial.begin(9600);
}

byte a[5] = {1, 2, 3, 4, 5};
byte b[3];
void loop() {

  //  while (mySerial.available())
  //    Serial.write("as" + mySerial.read());

//  while (mySerial.available() < 3) {}
//
//  for (int n = 0; n < 3; n++)
//    b[n] = mySerial.read(); // Then: Get them.
//
//  Serial.print(b[0]);
//  Serial.print(" ");
//  Serial.print(b[1]);
//  Serial.print(" ");
//  Serial.print(b[2]);
//  Serial.println(" ");

  //    if (Serial.available())
    mySerial.write(a, sizeof(a));

    delay(100);
}

