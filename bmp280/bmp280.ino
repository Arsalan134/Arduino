#include <Wire.h>
#include <SPI.h>
#include <Math.h>
#include <Adafruit_BMP280.h>

//#define BMP_SCK 13 //scl
//#define BMP_MISO 12 //sdo
//#define BMP_MOSI 11 //sda
//#define BMP_CS 10 //csb

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  Serial.print("Temperature\t");
  Serial.print(bmp.readTemperature());
  Serial.println("°C");

  Serial.print("Pressure\t");
  Serial.print(bmp.readPressure() / 133.3); // paskal / 133.3 =  mmrs
  Serial.println(" mm");

  Serial.print("Approx altitude\t");
  Serial.print(bmp.readAltitude()); // this should be adjusted to your local forcase 1013.25
  Serial.println(" m");
  
  Serial.println();
  delay(2000);


}
