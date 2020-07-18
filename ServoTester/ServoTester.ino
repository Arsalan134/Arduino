#include <Servo.h>

Servo stearingServo, throttle;

int pos = 0;

void setup() {
  stearingServo.attach(3);
//    throttle.attach(5);
  throttle.attach(5, 1000, 2000);
  Serial.begin(115200);

  throttle.write(180);
  delay(2000);
  throttle.write(0);
}

int mini = 40;
int maxi = 140;

//short minThrottle = 1000;
//short maxThrottle = 2000;


void loop() {
  delay(100);
  
  for (pos = mini; pos <= maxi; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    stearingServo.write(pos);              // tell servo1 to go to position in variable 'pos'
    Serial.println(pos);
    delay(5);                       // waits 15ms for the servo to reach the position
  }

  for (pos = maxi; pos >= mini; pos -= 1) { // goes from 180 degrees to 0 degrees
    stearingServo.write(pos);              // tell servo1 to go to position in variable 'pos'
    Serial.println(pos);
    delay(5);                       // waits 15ms for the servo to reach the position
  }

  delay(1000);

//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    throttle.write(pos);
//    Serial.println(pos);
//    delay(10);                       // waits 15ms for the servo to reach the position
//  }
//
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    throttle.write(pos);              // tell servo1 to go to position in variable 'pos'
//    Serial.println(pos);
//    delay(10);                       // waits 15ms for the servo to reach the position
//  }

}
