#include <Wire.h>
#include <SPI.h>
#include <PS4USB.h>

#include <Math.h>
#include <LiquidCrystal_I2C.h>

#include "printf.h"

#include <SoftwareSerial.h>
SoftwareSerial radio(10, 11);

#include "printf.h"

USB Usb;
PS4USB PS4(&Usb);
bool printAngle, printTouch;

bool emergencyStop = false;

byte valueOfVibration;
byte vibrationMinThreshold = 10;

byte minForAcc = 125;
byte maxForAcc = 210;

byte sliderPin = A0;
byte degreeOfFreedomPin = A1;

const byte delayTime = 10;

boolean timeout = true;

struct TransmitData {
  byte roll, pitch, yaw, throttle, degreeOfFreedom;
};

struct RecieveData {
  byte temperature, altitude, vibration;
};

TransmitData tData = {0, 1, 2, 3, 4};
RecieveData rData = {0, 1, 2};

//RF24 radio(7, 8);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


byte degree[8] = {
  14,
  10,
  14,
  0,

  0,
  0,
  0,
  0
};

//const uint64_t addresses[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

byte transmitData[5];
byte recievedData[5];

void setup() {

  Serial.begin(115200);
  radio.begin(9600);

  printf_begin();

  lcd.begin(16, 2);

  lcd.createChar(0, degree);

  lcd.setBacklight(255);
  lcd.clear();

  lcd.print("Willkommen");
  lcd.setCursor(8, 1);
  lcd.print("Arsalan");

  delay(500);

  lcd.clear();

  while (Usb.Init() == -1) {
    Serial.println("OSC didn't start");
    lcd.print("OSC didn't start");
    delay(500);
    lcd.clear();
  }

  Usb.Task();

  Serial.println("PS4 USB Library Started");

  //  radio.begin();
  //  radio.setAutoAck(false);
  //  radio.setPALevel(RF24_PA_MAX);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.setCRCLength(RF24_CRC_8);
  //  radio.setPayloadSize(sizeof(transmitData));
  //  radio.openWritingPipe(addresses[1]);
  //  radio.openReadingPipe(1, addresses[0]);
  //  radio.printDetails();
  //  radio.startListening();

}

void printTransmitData() {
  Serial.print("Send: ");
  lcd.home();

  for (int i = 0; i < sizeof(transmitData) / sizeof(transmitData[0]); i++) {
    Serial.print(transmitData[i]);
    Serial.print(" ");
  }
  Serial.println();

  lcd.print(transmitData[tData.roll]);

  lcd.print(" ");

  lcd.setCursor(4, 0);
  lcd.print(transmitData[tData.pitch]);

  lcd.print(" ");

  lcd.setCursor(8, 0);
  lcd.print(transmitData[tData.yaw]);

  lcd.print(" ");

  lcd.setCursor(12, 0);

  //    if (!emergencyStop)
  //      lcd.print(transmitData[tData.throttle]);
  //    else
  //      lcd.print("STOP");
  //
  //    lcd.setCursor(15, 0);

  lcd.print(transmitData[tData.degreeOfFreedom]);
  lcd.write(byte(0));
  lcd.print("     ");
}

void printRecievedData() {
  Serial.print("Recieved: ");
  lcd.setCursor(0, 1);
  for (int i = 0; i < sizeof(recievedData) / sizeof(recievedData[0]); i++) {
    Serial.print(recievedData[i]);
    Serial.print(" ");
  }
  Serial.println();

  if (PS4.connected()) {
    lcd.print(recievedData[rData.temperature]);

    lcd.write(byte(0));
    lcd.print("C ");

    lcd.print(recievedData[rData.altitude]);
    lcd.print("m");

    lcd.print("         ");
  }
}

void transmit() {
  Serial.println("Transmitting...");
  radio.write(transmitData, sizeof(transmitData));
}

void listen() {
  Serial.println("Listening...");
  unsigned long startedWaitingAt = micros();               // Set up a timeout period, get the current microseconds
  timeout = false;

  while (!radio.available())                              // While nothing is received
    if (micros() - startedWaitingAt > 200000) {        // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }

  while (radio.available()) {
    //    recievedData = radio.read();
    Serial.println("SSS" + radio.read());
  }

  valueOfVibration = recievedData[rData.vibration];

}

void loop() {

  // default values
  transmitData[tData.roll] = 127;
  transmitData[tData.pitch] = 127;
  transmitData[tData.yaw] = 127;
  transmitData[tData.degreeOfFreedom] = map(analogRead(degreeOfFreedomPin), 0, 1023, 180, 0);

  int throttle = !emergencyStop ? analogRead(sliderPin) : 0;
  transmitData[tData.throttle] = map(throttle, 0, 1024, 0, 255);

  recievedData[rData.temperature] = 0;
  recievedData[rData.altitude] = 0;
  recievedData[rData.vibration] = 0;

  Usb.Task();

  if (PS4.connected()) {

    lcd.setCursor(4, 1);

    //    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
    transmitData[tData.roll] = PS4.getAnalogHat(LeftHatX);
    transmitData[tData.pitch] = PS4.getAnalogHat(RightHatY);
    //    }

    if (PS4.getAnalogButton(L2)) {
      byte value = PS4.getAnalogButton(L2);
      transmitData[tData.yaw] = map(value, 0, 255, 127, 0);
    }

    if (PS4.getAnalogButton(R2)) {
      byte value = PS4.getAnalogButton(R2);
      transmitData[tData.yaw] = map(value, 0, 255, 128, 255);
    }

    valueOfVibration = (valueOfVibration < vibrationMinThreshold) ? 0 : valueOfVibration;
    PS4.setRumbleOn(valueOfVibration, valueOfVibration);

    //    if (PS4.getButtonClick(PS))
    //      Serial.print("\r\nPS");
    //    if (PS4.getButtonClick(TRIANGLE)) {
    //      Serial.print("\r\nTraingle");
    //      PS4.setRumbleOn(RumbleLow);
    //  }
    //    if (PS4.getButtonClick(CIRCLE)) {
    //      Serial.print("\r\nCircle");
    //      PS4.setRumbleOn(RumbleHigh);
    //    }
    //    if (PS4.getButtonClick(CROSS)) {
    //      Serial.print("\r\nCross");
    //      PS4.setLedFlash(10, 10); // Set it to blink rapidly
    //    }

    if (PS4.getButtonClick(SQUARE)) {
      emergencyStop = !emergencyStop;
    }

    if (PS4.getButtonClick(UP)) {
      Serial.print("\r\nUp");
      PS4.setLed(Red);
    } if (PS4.getButtonClick(RIGHT)) {
      Serial.print("\r\nRight");
      PS4.setLed(Blue);
    } if (PS4.getButtonClick(DOWN)) {
      Serial.print("\r\nDown");
      PS4.setLed(Yellow);
    } if (PS4.getButtonClick(LEFT)) {
      Serial.print("\r\nLeft");
      PS4.setLed(Green);
    }

    //    if (PS4.getButtonClick(L1))
    //      Serial.print("\r\nL1");
    //    if (PS4.getButtonClick(L3))
    //      Serial.print("\r\nL3");
    //    if (PS4.getButtonClick(R1))
    //      Serial.print("\r\nR1");
    //    if (PS4.getButtonClick(R3))
    //      Serial.print("\r\nR3");

    //    if (PS4.getButtonClick(SHARE))
    //      Serial.print("\r\nShare");
    if (PS4.getButtonClick(OPTIONS)) {
      Serial.print("\r\nOptions");
      printAngle = !printAngle;
    }
    //    if (PS4.getButtonClick(TOUCHPAD)) {
    //      Serial.print(F("\r\nTouchpad"));
    //      printTouch = !printTouch;
    //    }

    if (printAngle) {
      int rollValueFromController = PS4.getAngle(Roll);
      rollValueFromController = constrain(rollValueFromController, minForAcc, maxForAcc);
      transmitData[tData.roll] = map(rollValueFromController, minForAcc, maxForAcc, 0, 255);

      int pitchValueFromController = PS4.getAngle(Pitch);
      pitchValueFromController = constrain(pitchValueFromController, minForAcc, maxForAcc);
      transmitData[tData.pitch] = map(pitchValueFromController, minForAcc, maxForAcc, 255, 0);
    }

    //    if (printTouch) { // Print the x, y coordinates of the touchpad
    //      if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
    //        Serial.print(F("\r\n"));
    //      for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
    //        if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
    //          Serial.print("X"); Serial.print(i + 1); Serial.print(F(": "));
    //          Serial.print(PS4.getX(i));
    //          Serial.print("\tY"); Serial.print(i + 1); Serial.print(F(": "));
    //          Serial.print(PS4.getY(i));
    //          Serial.print("\t");
    //        }
    //      }
    //    }

  } else {
    lcd.setCursor(0, 1);
    lcd.print("PS4 is offnline");
  }

  transmit();

  delay(delayTime);

  listen();

  //  if (!timeout) {
  printTransmitData();
  printRecievedData();
  //  } else {
  if (!timeout) {
    lcd.clear();
    Serial.println("Failed timeout");
    lcd.print("Unreachable");
  }

}

