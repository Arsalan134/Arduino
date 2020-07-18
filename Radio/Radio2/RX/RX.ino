
//Domino60
//https://www.facebook.com/UPRFcom/?ref=hl
//https://www.youtube.com/channel/UCUNvg9PtBCzfdBN74TIoFFA
// Video: https://www.youtube.com/watch?v=0AyjlQ-YcJ0
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int dataReceived[6];

unsigned long pM = 0;
const long interval = 1000;
int bS = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  Serial.println("Start");
  radio.printDetails();
}

int x = 0;

void loop() {
  unsigned long cM = millis();
  if (radio.available()) {
    radio.read(dataReceived, sizeof(dataReceived));
    x++;
    bS = dataReceived[3];

    if (cM - pM >= interval) {
      pM = cM;
      Serial.print("Data: ");
      Serial.print(" Da1: "); Serial.print(dataReceived[0]);
      Serial.print(" Da2: "); Serial.print(dataReceived[1]);
      Serial.print(" Da3: "); Serial.print(dataReceived[2]);
      Serial.print(" Da4: "); Serial.print(dataReceived[3]);
      Serial.print(" Da5: "); Serial.print(dataReceived[4]);
      Serial.print(" Da6: "); Serial.print(dataReceived[5]);
      Serial.print("Pcks: "); Serial.println(x);
      x = 0;
    }
  }
}

