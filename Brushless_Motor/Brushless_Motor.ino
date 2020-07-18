#include <Servo.h>

Servo motor;

short motorPin = 6;
short sliderPin = 1;
short lastValue = 0;

short min = 800;
short max = 2000;

void setup() {
  motor.attach(motorPin);

  Serial.begin(115200);

  //  motor.write(max);
  //  delay(2000);

  //  motor.write(min);
  //  delay(6000);
}

void loop() {
  int throttle = analogRead(sliderPin);
  throttle = map(throttle, 0, 1023, min, max);
  if (throttle != lastValue) {
    motor.writeMicroseconds(throttle);
    Serial.println(percentage(throttle));
    lastValue = throttle;
  }
}

short percentage(int n) {
  return map(n, min, max, 0, 100);
}


