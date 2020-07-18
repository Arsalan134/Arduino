#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

int pause = 300;

void setup() {
  Serial.begin(9600);
  lcd.begin (16, 2);
  lcd.setBacklight(HIGH);
  lcd.autoscroll();
}

void loop() {
  lcd.setCursor(16, 0);
  printString("ADA University"); //  max 40 chars

  lcd.setCursor(16, 1);
  printString("Arsalan ADA telebesidir.");
}

void printString(String string) {
  for (int i = 0 ; i < string.length(); i++) {
    lcd.print(string.charAt(i));
    delay(pause);
  }
}

