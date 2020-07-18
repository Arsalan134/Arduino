//Domino60
//https://www.facebook.com/UPRFcom/?ref=hl
//https://www.youtube.com/channel/UCUNvg9PtBCzfdBN74TIoFFA
// Video: https://www.youtube.com/watch?v=0AyjlQ-YcJ0
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int dataToSend[6];

const int button = 3;
int bS = 0;
int Da6;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe);
  pinMode(button, INPUT);
  radio.printDetails();
  Serial.println("Start");
}

void loop() {

  bS = digitalRead(button);

  int sensor_1 = analogRead(A0);
  int Da1 = sensor_1;
  int sensor_2 = analogRead(A1);
  int Da2 = sensor_2;
  int sensor_3 = analogRead(A2);
  int Da3 = sensor_3;
  int sensor_4 = analogRead(A3);
  int Da5 = sensor_4;

  int Da4 = bS;
  Da6 = 111;

  dataToSend[0] = Da1;
  dataToSend[1] = Da2;
  dataToSend[2] = Da3;
  dataToSend[3] = Da4;
  dataToSend[4] = Da5;
  dataToSend[5] = Da6;

  radio.write(dataToSend, sizeof(dataToSend));
}

