// Пример, передача/прием данных через nRF24L01
// Связь только в одну сторону

#include <SPI.h>
#include "RF24.h"

// Индитификатор "трубы" (должен быть одинаковый у приемника и передатчика)
// Для каждой пары Приемник/Передатчик (направления передачи) должна быть создана отдельная труба (макс 6)
const uint64_t pipe = 0xF0F0F0F0F0LL;

// Конфигурация выводов CE, CSN (любые цифровые выводы)
// Передатчик
//RF24 radio(48, 53);      // для MEGA2560 (для моей)
//const int ledPin = 13;   // для MEGA2560 (для моей)
// Приемник
//RF24 radio(A0, 10);    // для Pro Mini (для моей)
//const int ledPin = A1; // для Pro Mini (для моей)
RF24 radio(7, 8);    // для Pro Mini (для моей)
const int ledPin = 13; // для Pro Mini (для моей)

// Тип платы (0)Передатчик/(1)Приемник
const boolean transmitter = false;

// Массив для данных
byte data[6], CRC;

// Состояние мигалки
int LedState = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(9); // канал (0-127)

  // Скорость, RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  // (меньше скорость, выше чувствительность приемника)
  //  radio.setDataRate(RF24_250KBPS);

  // Мощьность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, RF24_PA_HIGH=0dBm
  //  radio.setPALevel(RF24_PA_HIGH);

  // Тип платы (0)Передатчик/(1)Приемник
  if (transmitter) {
    // ПЕРЕДАТЧИК
    radio.openWritingPipe(pipe);   // открываем трубу на передачу
  } // if (transmitter == 0)
  else {
    // ПРИЕМНИК
    radio.openReadingPipe(1, pipe); // открываем первую трубу на прием с индитификатором 1
    radio.startListening();        // включаем приемник, начинаем слушать трубу
  } // else if (transmitter == 0)
}

void loop() {
  if (transmitter) {
    // ПЕРЕДАТЧИК
    // Для примера будем отправлять 5 произвольных данных + 1 CRC (сумма)
    data[0] = random(256);
    data[1] = random(256);
    data[2] = random(256);
    data[3] = random(256);
    data[4] = random(256);
    data[5] = data[0] + data[1] + data[2] + data[3] + data[4]; // CRC

    // Отправляем данные - указатель на данные и количество байт
    radio.write(&data, sizeof(data)); // отправляем данные и указываем сколько байт пакет

    Serial.print("SEND: ");
    Serial.print(data[0]);
    Serial.print(" - ");
    Serial.print(data[1]);
    Serial.print(" - ");
    Serial.print(data[2]);
    Serial.print(" - ");
    Serial.print(data[3]);
    Serial.print(" - ");
    Serial.print(data[4]);
    Serial.print(" = ");
    Serial.println(data[5]);

    delay(300);
  } else {
    // ПРИЕМНИК
    // проверяем пришли ли данные
    if (radio.available()) {
      // Принимаем данные - указатель на данные и количество байт
      radio.read(&data, sizeof(data));

      // расчитываем CRC принятых данных
      CRC = data[0] + data[1] + data[2] + data[3] + data[4];

      // проверяем CRC
      if (data[5] == CRC) {
        // Переключаем "Мигалку"
        // выводим в порт данные
        Serial.print("RCV (");
        Serial.print(sizeof(data));
        Serial.print("): ");
        Serial.print(data[0]);
        Serial.print(" - ");
        Serial.print(data[1]);
        Serial.print(" - ");
        Serial.print(data[2]);
        Serial.print(" - ");
        Serial.print(data[3]);
        Serial.print(" - ");
        Serial.print(data[4]);
        Serial.print(" = ");
        Serial.print(data[5]);
        Serial.print(" (");
        Serial.print(CRC);
        Serial.println(")");
      }
    }
  }
}
