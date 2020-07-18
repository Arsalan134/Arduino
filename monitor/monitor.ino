#include <Wire.h>
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

void setup() {
  lcd.begin (16, 2);
  lcd.setBacklight(HIGH);
}

void loop() {
  lcd.setCursor (0, 0); //(column,row)
  lcd.print("Willkommen, Azer!");
  delay(500);
  lcd.setCursor (0, 1); //(column,row)
  lcd.print("Wie geht es dir?");
}

