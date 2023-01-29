const byte linePin = D1;   // D1 Line HS
const byte framePin = D2;  // D2 Frame VS
const byte syncOut = D4;    // D4 TV sync out
// при подключенном к выходу Д4 ПАЛ-кодера ESP8266 не заводится,
// надо отключить видео выход при включении питания Спектрума

int hs_count = 0;

IRAM_ATTR void frameSync() {
  if (hs_count > 30) {
    digitalWrite(syncOut, 0);
    hs_count = 0;
  }
  hs_count += 1;
}

IRAM_ATTR void lineSync() {
  if (hs_count > 2) {
    digitalWrite(syncOut, 0);
    delayMicroseconds(4);
    digitalWrite(syncOut, 1);
  }
  hs_count++;
}

void setup() {
  Serial.begin(19200);
  pinMode(syncOut, OUTPUT);
  pinMode(linePin, INPUT_PULLUP);
  pinMode(framePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(linePin), lineSync, FALLING);
  attachInterrupt(digitalPinToInterrupt(framePin), frameSync, FALLING);
}

void loop() {
}