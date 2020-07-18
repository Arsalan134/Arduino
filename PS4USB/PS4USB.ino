#include <UTFT.h> 
#include <URTouch.h>

//==== Creating Objects
UTFT    myGLCD(SSD1289,38,39,40,41); //Parameters should be adjusted to your Display/Schield model
URTouch  myTouch( 6, 5, 4, 3, 2);

//==== Defining Variables
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

extern unsigned int bird01[0x41A];

int x, y;

char currentPage, selectedUnit;

//Ultrasonic Sensor
const int VCC = 13;
const int trigPin = 11;
const int echoPin = 12;

long duration;
int distanceInch, distanceCm;

// RGB LEDs
const int redLed = 10;
const int greenLed = 9;
const int blueLed = 8;
int xR=38;
int xG=38;
int xB=38;

// Floppy Bird
int xP = 319;
int yP = 100;
int yB = 30;
int fallRateInt = 0;
float fallRate =0;
int score=0;
const int button = 14;
int buttonState = 0;

void setup() {
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  // Defining Pin Modes
  pinMode(VCC, OUTPUT); // VCC
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(VCC, HIGH); // +5V - Pin 13 as VCC

  drawHomeScreen();  // Draws the Home Screen
  currentPage = '0'; // Indicates that we are at Home Screen
  selectedUnit = '0'; // Indicates the selected unit for the first example, cms or inches
}
