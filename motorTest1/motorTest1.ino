
int motorPWM = 9;

void setup() {
  pinMode(motorPWM, OUTPUT);
  Serial.begin(9600);
}
int p = 30;
void loop() {
  for (int i = 0; i < 255; i++) {
    delay(p);
    Serial.println(i);
    analogWrite(motorPWM, i);
  }
  Serial.println("PAUSE");
  delay(2000);
  for (int i = 255; i > 0 ; i--) {
    delay(p);
    Serial.println(i);
    analogWrite(motorPWM, i);
  }
  Serial.println("END");
  delay(2000);
}
