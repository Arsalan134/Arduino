#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> // https://github.com/maniacbug/RF24


const uint64_t pipe = 0xF0F1F2F3F4LL; // идентификатор передачи, "труба"

RF24 radio(8, 9); // CE, CSN
int i = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  delay(2);
  radio.setChannel(9); // канал (0-127)

  // скорость, RF24_250KBPS, RF24_1MBPS или RF24_2MBPS
  // RF24_250KBPS на nRF24L01 (без +) не работает.
  // меньше скорость, выше чувствительность приемника.
  radio.setDataRate(RF24_1MBPS);

  // мощность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM,
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(pipe); // открываем трубу на передачу.
}


void loop()
{
  radio.write(&i, sizeof(i)); // отправляем данные и указываем сколько байт пакет
  Serial.print("Send: ");
  Serial.println(i);
  delay(1000);
  i++;
}
