void setup() {
    pinMode(21, INPUT_PULLUP);
    pinMode(22, INPUT_PULLUP);
    pinMode(23, INPUT_PULLUP);
    pinMode(24, INPUT_PULLUP);
    Serial.println("CAN BUS OK!");
    Serial.println("univButtonModule, khonsu / retropilot.org");
}

void loop() {
  unsigned char buttonState = 0x0;
  if (!digitalRead(21)) buttonState = 0x4;
  if (!digitalRead(22)) buttonState = 0x3;
  if (!digitalRead(23)) buttonState = 0x2;
  if (!digitalRead(24)) buttonState = 0x1;
  if ((!digitalRead(21) and !digitalRead(22)) or (!digitalRead(22) and !digitalRead(23)) or (!digitalRead(23) and !digitalRead(24)) or (!digitalRead(21) and !digitalRead(23)) or (!digitalRead(22) and !digitalRead(24)) or (!digitalRead(21) and !digitalRead(24))) buttonState = 0x0;
  Serial.println(buttonState);
  delay(100);                       // send data per 100ms
}
