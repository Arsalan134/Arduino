const int inPin = 2;
void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT);
  digitalWrite(inPin, HIGH);
}

void loop() {
  delay(100);
  Serial.println(get_rpm());
}

int get_rpm() {
  int acct = 0;
  boolean IR = 0;
  unsigned long Time = 0;
  unsigned long sTime = millis();

  while (Time <= 1000) {
    if (digitalRead(inPin) == 1)
      IR = HIGH;
    if (digitalRead(inPin) == 0 && IR == 1) {
      acct++;
      IR = 0;
    }
    Time = millis() - sTime;
  }

  Serial.print("RPM: ");
//  return int(60000. / float(1000)) * acct;
  return acct;
}
