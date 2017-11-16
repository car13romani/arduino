int incomingByte = 0;
 
void setup() {
  // открываем serial порт на скорости 57600
  Serial.begin(57600);
}
 
void loop() {
  // если есть данные для передачи
  if (Serial.available()) {
    // получаем эти данные
    incomingByte = Serial.read();
    Serial.print(incomingByte);
    // передаем данные в порт
    incomingByte = 1234;
    Serial.print(incomingByte);
  }
}
